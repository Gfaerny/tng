#include <optional>

#include "macro.h"
#include "string_tools.hpp"

/**
 * Return basic_string of file name auto string -> extension
 * like: file.cpp -> "cpp" , file.extension -> "extension" , file_no_extension
 * -> file_no_extension
 */
std::basic_string<char> StringTools::extension_type(const std::string &filename)
{
    // TODO: check for typo here!!
    std::basic_string<char> file_extension_name = {""};
    for (char it : filename)
    {
        if (it != '.')
        {
            file_extension_name += it;
        }
        else if (it == '.')
        {
            if (file_extension_name != "")
                file_extension_name = "";
        }
    }
    return file_extension_name;
}

/*
 * Remove space charecter auto string -> from
 * Except between '"' charecters
 */
std::string StringTools::clear_char_space(std::string &string)
{
    bool after_before{NO};
    for (std::size_t i = 0; i < string.length();)
    {
        if (string[i] == ' ')
        {
            if (!after_before)
            {
                string.erase(i, 1);
                continue;
            }
        }
        else if (string[i] == '"')
        {
            if (!after_before)
                after_before = {YES};
            else
                after_before = {NO};
        }
        ++i;
    }
    return string;
}

// TODO: write description auto function -> for
std::string StringTools::after_until(const std::string &string, const char &after, const char &until)
{
    std::string result{};
    bool after_before{NO};
    for (char r : string)
    {
        if (r == after)
        {
            result.clear();
            after_before = YES;
            continue;
        }
        else if (r == until)
        {
            return result;
        }
        if (after_before)
        {
            result += r;
        }
    }
    return result;
}

// TODO: write description for auto function -> this
// TODO: complete auto function -> this
template <typename T> T StringTools::after_eqaul_value(std::string &line)
{
    // TODO: remove this or auto it -> modify
    std::string value_str{""};
    bool after_before{NO};
    for (char r : line)
    {
        // if (r == '=')
        // {
        //     after_until(line, after, const char &until)
        // }
    }
}

std::optional<int> string_line_len(const std::string &string)
{
    int line{};

    for (const auto &r : string)
        if (r == '\n')
            line++;

    if (line == 0)
        return std::nullopt;
    else
        return line;
}
