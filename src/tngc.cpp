#include <cstdlib>
#include <fstream>

#include "config.hpp"
#include "macro.h"
#include "search.hpp"
#include "tngc.hpp"
#include <error.hpp>

// no space in variable and field name strings
// " cpp" [X] "cpp" [Y]
auto read_set_tngc(ConfigData &config_data) -> void
{
    std::ifstream config_stream(config_path);
    // std::ifstream sdas(config_path, std::ios::binary);
    debug_prt("file %s got target as config file.\n", config_path.c_str());

    if (!config_stream)
    {
        throw tng_error{
            .error_massage{"tng error : config file can not be open."}};
    }

    std::string line{""}, field_string{""}, variable_string{""},
        value_string{""}, valueStr_string{""}, valueStrMl_string{""};

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

        if (line [first] == '#')
            continue;

        for (char c : line)
        {
            column_count++;

            // In this scope of if's statements we just set `State` of `state`
            if (c == '[')
            {
                if (state == State::line_start || state == State::value_done ||
                    state == State::value_string_done ||
                    state == State::value_string_multi_line_done)
                {
                    state = State::reading_section_feild;
                }
                else
                {
                    throw tng_error{
                        .error_massage =
                            tepic_error_massages::TNGC_UNEXCEPT_SEC_DEF_ACT(
                                line_count, column_count)};
                }
            }

            else if (c == '#')
            {
                if (state != State::line_start && state != State::value_done &&
                    state != State::value_string_done &&
                    state != State::value_string_multi_line_done)
                {
                    throw tng_error{
                        .error_massage =
                            tepic_error_massages::TNGC_UNEXEC_COMMENT(
                                line_count, column_count)};
                }
                break;
            }

            else if (c == ']')
            {
                if (state == State::reading_section_feild)
                {
                    state = State::section_done;
                }
                else
                {
                    throw tng_error{
                        .error_massage =
                            tepic_error_massages::TNGC_UNEXCEPT_SEC_DEF_ACT(
                                line_count, column_count)};
                }
            }

            else if (c == '=')
            {
                if (state == State::reading_variable) // auto variable -> check
                {
                    config_data.push_variable_value(variable_string, YES,
                                                    line_count, column_count);
                    state = State::reading_value;

                    variable_string.clear();
                }
                else
                {
                    throw tng_error{.error_massage =
                                        tepic_error_massages::TNGC_UNEXEC_EQUEL(
                                            line_count, column_count)};
                }
            }

            else if (c == '\"')
            {
                if (state == State::reading_value)
                {
                    if ((line.size() - column_count) == 3)
                    {
                        if (line [column_count + 1] == '\"' &&
                            line [column_count + 2] == '\"' &&
                            line [column_count + 3] == '\n')
                        {
                            state = State::reading_string_multi_line_value;
                        }
                    }
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
                        if (line [column_count + 1] == '\"' &&
                            line [column_count + 2] == '\"' &&
                            line [column_count + 3] == '\n')
                        {
                            state = State::value_string_multi_line_done;
                        }
                    }
                    else
                    {
                        throw tng_error{
                            .error_massage =
                                tepic_error_massages::TNGC_UNCLOSE_ML_EQUEL(
                                    line_count, column_count)};
                    }
                }
                else
                {
                    throw tng_error{.error_massage =
                                        tepic_error_massages::TNGC_UNEXEC_QUOTE(
                                            line_count, column_count)};
                }
            }

            else if (c == '\n')
            {
                if (state == State::section_done)
                {
                    state = State::line_start;
                }
                else if (state == State::value_string_done ||
                         state == State::value_string_multi_line_done ||
                         state == State::reading_value)
                {
                    if (state == State::value_string_done)
                    {
                        config_data.push_variable_value(
                            valueStr_string, NO, line_count, column_count);
                        valueStr_string.clear();
                    }
                    else if (state == State::value_string_multi_line_done)
                    {
                        config_data.push_variable_value(
                            valueStrMl_string, NO, line_count, column_count);
                        valueStrMl_string.clear();
                    }
                    else if (state == State::reading_value)
                    {
                        config_data.push_variable_value(
                            value_string, NO, line_count, column_count);
                        value_string.clear();
                    }
                    state = State::line_start;
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
                    std::printf("%s", field_string.c_str());
                    if (!Search::if_element_exist(config_data.sections,
                                                  config_data.current_index))
                        config_data.sections.emplace_back();

                    config_data.sections [config_data.current_index].push_field(
                        field_string, line_count, column_count);

                    field_string.clear();
                }
                else if (c == ']')
                {
                    std::printf("%s", field_string.c_str());

                    if (!Search::if_element_exist(config_data.sections,
                                                  config_data.current_index))
                        config_data.sections.emplace_back();

                    config_data.sections [config_data.current_index].push_field(
                        field_string, line_count, column_count);

                    field_string.clear();
                }
                else
                    field_string += c;
            }

            else if (state == State::line_start && std::isalpha(c))
            {
                state = State::reading_variable;
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
                config_data.push_variable_value(value_string, NO, line_count,
                                                column_count);

                value_string.clear();
            }

            else if (state == State::value_string_done)
            {
                config_data.push_variable_value(valueStrMl_string, NO,
                                                line_count, column_count);

                valueStrMl_string.clear();
            }
        }
    }

    return;
}
