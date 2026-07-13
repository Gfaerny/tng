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

    std::string line{""}, section_field_string{""}, variable_string{""}, value_string{""};
    State state = State::line_start;

    while (std::getline(config_stream, line))
    {
        // Add new line charecter to line string for state declaration
        line += '\n';

        if (line[0] == '#')
            continue;

        for (char c : line)
        {
            // In this scope of if's statements we just set `State` of `state`
            if (c == '[')
            {
                if (state == State::line_start)
                {
                    state = State::reading_section_feild;
                }
                else
                {
                    // TODO: thorw error
                }
            }

            else if (state == State::line_start && std::isalpha(c))
            {
                state = State::reading_variable;
            }

            else if (c == ']')
            {
                if (state == State::reading_section_feild)
                {
                    state = State::section_done;
                }
                else
                {
                    // TODO: throw error
                }
            }

            else if (c == '=')
            {
                if (state == State::reading_variable) // check variable
                {
                    config_data.pushVarableElement(variable_string);
                    variable_string.clear();
                    state = State::reading_value;
                }
                else
                {
                    // TODO: throw error
                }
            }

            else if (c == '\"')
            {
                if (state == State::reading_value)
                {
                    state = State::reading_string_value;
                }
                else
                {
                    // TODO: throw error
                }
            }

            else if (c == '\n')
            {
                if (state == State::section_done)
                {
                    state = State::line_start;
                }
                else if (state == State::reading_value)
                {
                    config_data.pushValueElement(value_string);
                    value_string.clear();
                    state = State::line_start;
                }
                else
                {
                    // TODO: throw error
                }
            }

            // Checking state and current charecter for it
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

            else if (state == State::reading_variable)
            {
                variable_string += c;
            }

            else if (state == State::reading_value)
            {
                value_string += c;
            }
        }
    }

    return;
}
