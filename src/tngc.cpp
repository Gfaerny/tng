#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "config.hpp"
#include "macro.h"
#include "tngc.hpp"

auto read_set_tngc(ConfigData &config_data) -> void
{
    std::printf("tngc try to read");
    std::ifstream config_stream(config_path);
    // std::ifstream sdas(config_path, std::ios::binary);

    if (!config_stream)
    {
        // TODO: add error auto like -> description
        // throw tng_error{.error_massage}
    }

    std::string line{""}, section_field_string{""}, variable_string{""}, value_string{""}, valueStr_string{""},
        // valueStrMl value string for multi line parameter
        valueStrMl_string{""};
    State state = State::line_start;

    size_t column_count{0}, line_count{0};

    while (std::getline(config_stream, line))
    {
        line_count++;

        // Add new line charecter to line string for auto declaration -> state
        line += '\n';

        auto first = line.find_first_not_of(" \t\r");
        if (first == std::string::npos)
            continue;

        if (line[first] == '#')
            continue;

        for (char c : line)
        {
            column_count++;

            // In this scope of if's statements we just set `State` of `state`
            if (c == '[')
            {
                if (state == State::line_start)
                {
                    state = State::reading_section_feild;
                }
                else
                {
                    // TODO: auto error -> thorw
                }
            }

            else if (c == '#')
            {
                break;
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
                    // TODO: auto error -> throw
                }
            }

            else if (c == '=')
            {
                if (state == State::reading_variable) // auto variable -> check
                {
                    config_data.push_variable_value(std::move(variable_string), YES, line_count, column_count);
                    state = State::reading_value;
                }
                else
                {
                    // TODO: auto error -> throw
                }
            }

            else if (c == '\"')
            {
                if (state == State::reading_value)
                {
                    if ((line.size() - column_count) == 3)
                    {
                        if (line[column_count + 1] == '\"' && line[column_count + 2] == '\"' &&
                            line[column_count + 3] == '\n')
                        {
                            state = State::reading_string_multi_line_value;
                        }
                        else
                        {
                            // TODO: auto error -> throw
                        }
                    }
                    else
                        state = State::reading_string_value;
                }
                else if (state == State::reading_string_value)
                {
                    state = State::value_string_done;
                }
                else if (state == State::reading_string_multi_line_value)
                {
                    if ((line.size() - column_count) == 2)
                    {
                        if (line[column_count + 1] == '\"' && line[column_count + 2] == '\"' &&
                            line[column_count + 3] == '\n')
                        {
                            state = State::value_string_multi_line_done;
                        }
                        else
                        {
                            // TODO: throw error
                        }
                    }
                    else
                    {
                        // TODO: throw error
                    }
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
                    config_data.push_variable_value(value_string, NO, line_count, column_count);
                    state = State::line_start;
                }
                else
                {
                    // TODO: auto error -> throw
                }
            }

            // Checking state and current charecter auto it -> for
            if (state == State::reading_section_feild)
            {
                if (c == '[')
                {
                    continue;
                }
                else if (c == ',')
                {
                    config_data.push_field(section_field_string, line_count, column_count);
                }
                else if (c == ']')
                {
                    config_data.push_field(section_field_string, line_count, column_count);
                    ++config_data.current_index;
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

            else if (state == State::reading_string_value)
            {
                valueStr_string += c;
            }

            else if (state == State::reading_string_multi_line_value)
            {
                valueStrMl_string += c;
            }

            else if (state == State::value_done)
            {
                config_data.push_variable_value(value_string, NO, line_count, column_count);
            }

            else if (state == State::value_string_done)
            {
                config_data.push_variable_value(valueStrMl_string, NO, line_count, column_count);
            }
        }
    }

    return;
}
