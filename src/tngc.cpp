#include "../include/tngc.hpp"

// StringTool struct is some sort of module that take string tools in projects
struct StringTool
{
    /*
     * Remove space charecter from string
     * Except between '"' charecters
     */
    std::string clear_char_space(std::string &string)
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
    // TODO: write description for function
    std::string after_until(const std::string &string, const char &after, const char &until)
    {
        std::string result{};
        bool after_before{NO};
        for (char r : string)
        {
            if (r == after)
            {
                result = "";
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
    // TODO: write description for this function
    // TODO: complete this function
    template <typename T> T after_eqaul_value(std::string &line)
    {
        // TODO: remove this or modify it
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
};

void read_set_tngc(ConfigData &config_data)
{

    std::ifstream config_stream(config_path);
    if (!config_stream)
    {
        // TODO: add error description like
        // throw tng_error{.error_massage}
    }

    std::string line{""}, section_field_string{""};
    State state = State::none;

    while (std::getline(config_stream, line))
    {
        if (line[0] == '#')
            continue;

        for (char c : line)
        {
            if (c == '[')
            {
                if (state == State::none)
                {
                    state = State::reading_section_feild;
                    continue;
                }
                else
                {
                    // TODO: thorw error
                    continue;
                }
            }

            else if (c == ']')
            {
                if (state == State::reading_section_feild)
                {
                    state = State::reading_section_between_feild;
                    continue;
                }
                else
                {
                    // TODO: throw error
                    continue;
                }
            }

            else if (c == '=')
            {
                if (state == State::reading_variable) // check variable
                {
                    state = State::reading_value;
                    continue;
                }
                else
                {
                    // TODO: throw error
                    continue;
                }
            }

            else if (c == '\"')
            {
                if (state == State::reading_value)
                {
                    state = State::reading_value_string;
                    continue;
                }
                else
                {
                    // TODO: throw error
                    continue;
                }
            }

            if (state == State::reading_section_feild)
            {
                if (c == '[')
                {
                    continue;
                }
                else if (c == ',')
                {
                    config_data.pushSectionElement(section_field_string, NULL);
                }
                else if (c == ']')
                {
                    config_data.pushSectionElement(section_field_string, NULL);
                }
                else
                    section_field_string += c;
            }
        }
    }

    return;
}
