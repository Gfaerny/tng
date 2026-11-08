/* tngc.cpp - Configuration parser for the tng generator.  */

#include "tngc.hpp"
#include "error.hpp"

#include <cctype>
#include <charconv>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class token_kind
{
    tok_eof,
    tok_section_open,  /* [ */
    tok_section_close, /* ] */
    tok_equals,        /* = */
    tok_comma,         /* , */
    tok_identifier,    /* key or section field */
    tok_int,           /* interger value */
    tok_string,        /* "..." or ("...") */
    tok_boolean        /* YES or NO */
};

struct token
{
    token_kind kind;
    std::string_view text;
    std::size_t line;
    std::size_t column;
};

class lexer
{
  public:
    explicit lexer(std::string_view source)
        : src_(source), pos_(0), line_(1), col_(1)
    {
    }

    auto next_token() -> token
    {
        skip_whitespace_and_comments();

        if (pos_ >= src_.size())
            return token{token_kind::tok_eof, "", line_, col_};

        const std::size_t tok_line = line_;
        const std::size_t tok_col = col_;
        const char c = current();

        if (c == '[')
        {
            advance();
            return token{token_kind::tok_section_open, "[", tok_line, tok_col};
        }
        if (c == ']')
        {
            advance();
            return token{token_kind::tok_section_close, "]", tok_line, tok_col};
        }
        if (c == '=')
        {
            advance();
            return token{token_kind::tok_equals, "=", tok_line, tok_col};
        }
        if (c == ',')
        {
            advance();
            return token{token_kind::tok_comma, ",", tok_line, tok_col};
        }

        /* Multi-line string: (" ... ")  */
        if (c == '(' && peek(1) == '"')
        {
            return scan_multiline_string(tok_line, tok_col);
        }

        /* Single-line string: " ... "  */
        if (c == '"')
        {
            return scan_string(tok_line, tok_col);
        }

        /* Identifiers, keywords, booleans, or unquoted values.  */
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_' || c == '/')
        {
            return scan_identifier(tok_line, tok_col);
        }

        /* If unexpected token encountered, throw formatted error.  */
        throw tng_error{.error_massage = "tng error: unexpected character '" +
                                         std::string(1, c) + "' at line " +
                                         std::to_string(tok_line) + ":" +
                                         std::to_string(tok_col)};
    }

  private:
    std::string_view src_;
    std::size_t pos_;
    std::size_t line_;
    std::size_t col_;

    [[nodiscard]] auto current() const -> char
    {
        return src_ [pos_];
    }

    [[nodiscard]] auto peek(std::size_t offset) const -> char
    {
        if (pos_ + offset >= src_.size())
            return '\0';
        return src_ [pos_ + offset];
    }

    [[nodiscard]] auto is_int(std::string_view str) const -> bool
    {
        for (char c : str)
        {
            if (!std::isdigit(static_cast<unsigned char>(c)))
                return NO;
        }
        return YES;
    }

    auto advance() -> void
    {
        if (pos_ < src_.size())
        {
            if (src_ [pos_] == '\n')
            {
                line_++;
                col_ = 1;
            }
            else
            {
                col_++;
            }
            pos_++;
        }
    }

    auto skip_whitespace_and_comments() -> void
    {
        while (pos_ < src_.size())
        {
            const char c = current();
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                advance();
            }
            else if (c == '#')
            {
                /* Ignore comment line until newline.  */
                while (pos_ < src_.size() && current() != '\n')
                    advance();
            }
            else
            {
                break;
            }
        }
    }

    auto scan_string(std::size_t tok_line, std::size_t tok_col) -> token
    {
        advance(); /* Skip initial '"'  */
        const std::size_t start = pos_;

        while (pos_ < src_.size() && current() != '"')
        {
            if (current() == '\n')
                throw tng_error{.error_massage =
                                    "tng error: unclosed string literal at " +
                                    std::to_string(tok_line) + ":" +
                                    std::to_string(tok_col)};
            advance();
        }

        if (pos_ >= src_.size())
            throw tng_error{.error_massage =
                                "tng error: unclosed string literal at " +
                                std::to_string(tok_line) + ":" +
                                std::to_string(tok_col)};

        const std::string_view val = src_.substr(start, pos_ - start);
        advance(); /* Skip trailing '"'  */
        return token{token_kind::tok_string, val, tok_line, tok_col};
    }

    auto scan_multiline_string(std::size_t tok_line, std::size_t tok_col)
        -> token
    {
        advance(); /* Skip '('  */
        advance(); /* Skip '"'  */
        const std::size_t start = pos_;

        while (pos_ < src_.size())
        {
            if (current() == '"' && peek(1) == ')')
            {
                const std::string_view val = src_.substr(start, pos_ - start);
                advance(); /* Skip '"'  */
                advance(); /* Skip ')'  */
                return token{token_kind::tok_string, val, tok_line, tok_col};
            }
            advance();
        }

        throw tng_error{.error_massage =
                            "tng error: unclosed multi-line literal (\") at " +
                            std::to_string(tok_line) + ":" +
                            std::to_string(tok_col)};
    }

    auto scan_identifier(std::size_t tok_line, std::size_t tok_col) -> token
    {
        const std::size_t start = pos_;
        while (pos_ < src_.size())
        {
            const char c = current();
            if (std::isalnum(static_cast<unsigned char>(c)) || c == '_' ||
                c == '/' || c == '-' || c == '.')
                advance();
            else
                break;
        }

        const std::string_view text = src_.substr(start, pos_ - start);
        if (text == "YES" || text == "NO" || text == "yes" || text == "no" ||
            text == "true" || text == "false")
            return token{token_kind::tok_boolean, text, tok_line, tok_col};

        else if (is_int(text))
            return token{token_kind::tok_int, text, tok_line, tok_col};

        else
            return token{token_kind::tok_identifier, text, tok_line, tok_col};
    }
};

auto read_set_tngc(ConfigData &config_data) -> void
{
    std::ifstream config_stream(config_path, std::ios::binary);
    if (!config_stream)
        throw tng_error{.error_massage =
                            "tng error : config file can not be open."};

    std::ostringstream ss;
    ss << config_stream.rdbuf();
    const std::string file_content = ss.str();

    lexer lex(file_content);
    token tok = lex.next_token();

    while (tok.kind != token_kind::tok_eof)
    {
        /* 1. Parse Section Header: [ field1, field2, ... ] */
        if (tok.kind == token_kind::tok_section_open)
        {
            config_data.sections.emplace_back();
            const std::size_t cur_sec = config_data.sections.size() - 1;

            tok = lex.next_token();
            while (tok.kind != token_kind::tok_section_close)
            {
                if (tok.kind == token_kind::tok_identifier)
                {
                    config_data.sections [cur_sec].push_field(
                        std::string(tok.text), tok.line, tok.column);
                }
                else if (tok.kind != token_kind::tok_comma)
                {
                    throw tng_error{.error_massage =
                                        "tng error: expected field name in "
                                        "section definition."};
                }
                tok = lex.next_token();
            }
            tok = lex.next_token(); /* Skip ']' */
        }
        /* 2. Parse Variable Assignment: key = value */
        else if (tok.kind == token_kind::tok_identifier)
        {
            const std::string key(tok.text);
            const std::size_t k_line = tok.line;
            const std::size_t k_col = tok.column;

            tok = lex.next_token();
            if (tok.kind != token_kind::tok_equals)
                throw tng_error{.error_massage =
                                    "tng error: expected '=' after key."};

            tok = lex.next_token();
            if (tok.kind != token_kind::tok_string &&
                tok.kind != token_kind::tok_identifier &&
                tok.kind != token_kind::tok_boolean &&
                tok.kind != token_kind::tok_int)
            {
                throw tng_error{.error_massage =
                                    "tng error: expected valid value for key."};
            }

            /* Push variable and value according to ConfigData's API */
            config_data.push_variable_value(key, YES, k_line, k_col);
            config_data.push_variable_value(std::string(tok.text), NO, tok.line,
                                            tok.column);

            tok = lex.next_token();
        }
        else
        {
            throw tng_error{.error_massage = "tng error: unexpected token at " +
                                             std::to_string(tok.line) + ":" +
                                             std::to_string(tok.column)};
        }
    }
}
