#ifndef SECTION_HPP
#define SECTION_HPP

#include <string>
#include <string_view>
#include <vector>

struct MetaData
{
    size_t line{}, column{};
};

struct TokenValue
{
    std::string text{};
    MetaData metadata;

    auto set_text(std::string txt) -> void;
    auto set_metadata(MetaData md) -> void;

    auto get_metadata() const -> MetaData;
    auto get_value() const -> std::string;
};

struct VariableValue
{
    TokenValue variable;
    TokenValue value;

    auto push_metadata(size_t line, size_t column, bool var_val) -> void;

    /* return metadata if bool is 0 return variable.metadata */
    auto get_metadata(bool is_variable) -> MetaData const;

    auto get_variable() -> std::string_view const;
    auto get_value() -> std::string_view const;
};

struct Section
{
    std::vector<TokenValue> fields{};
    std::vector<VariableValue> variable_value{};

    /* Push in order fields */
    auto push_field(const std::string fieldStr, const size_t line, const size_t column) -> void;

    /* Push in order, variavble and value string with bool true or false value */
    auto push_var_val(const std::string variableOrvalue, const bool is_variable, const size_t line, const size_t column)
        -> void;
};

#endif
