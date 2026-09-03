#include "config.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "buffer.hpp"
#include "macro.h"
#include "section.hpp"
#include "string_tools.hpp"
#include "tngc.hpp"

auto ConfigData::push_variable_value(const std::string variable_value, bool is_variable, size_t line,
                                     const size_t column) -> void
{
    this->sections[this->current_index].push_var_val(variable_value, is_variable, line, column);
}
auto ConfigData::push_field(const std::string &field, const size_t &line, const size_t &column) -> void
{
    this->sections[current_index].push_field(field, line, column);
}

Config::Config()
{
    read_set_tngc(this->configData);
}

/*
 * Fill ConfigSectoinBuffer with section data
 */
auto Config::fill_config_buffer(const Section &section) -> void
{
    // Switch between aviable variable
    // If it was neccesry we add to configBuffer
    for (auto &variable_value : section.variable_value)
    {
        const auto &variable = variable_value.get_variable();
        const auto &value = variable_value.get_value();

        // Bool type variables
        if (variable == "comment")
        {
            if (value == "YES" || value == "true" || value == "yes")
            {
                configBuffer.comment = YES;
            }
            else if (value == "NO" || value == "false" || value == "no")
            {
                configBuffer.comment = NO;
            }
            else
            {
                // TODO: throw error
            }
        }
        else if (variable == "comment_style")
        {
            if (value == "block")
            {
                configBuffer.comment_style = YES;
            }
            else if (value == "line")
            {
                configBuffer.comment_style = NO;
            }
            else
            {
                // TODO: throw error
            }
        }
        else if (variable == "include_license_before_header")
        {
            if (value == "YES" || value == "true" || value == "yes")
            {
                configBuffer.include_license_before_header = YES;
            }
            else if (value == "NO" || value == "false" || value == "no")
            {
                configBuffer.include_license_before_header = NO;
            }
            else
            {
                // TODO: throw error
            }
        }
        else if (variable == "overwrite_existing_file")
        {
            if (value == "YES" || value == "true" || value == "yes")
            {
                configBuffer.overwrite_existing_file = YES;
            }
            else if (value == "NO" || value == "false" || value == "no")
            {
                configBuffer.overwrite_existing_file = NO;
            }
            else
            {
                // TODO: throw error
            }
        }
        else if (variable == "include_license")
        {
            if (value == "YES" || value == "true" || value == "yes")
            {
                configBuffer.include_license = YES;
            }
            else if (value == "NO" || value == "false" || value == "no")
            {
                configBuffer.include_license = NO;
            }
            else
            {
                // TODO: throw error
            }
        }

        // String type variables
        else if (variable == "block_header")
            configBuffer.block_header = value;

        else if (variable == "block_line_prefix")
            configBuffer.block_line_prefix = value;

        else if (variable == "block_footer")
            configBuffer.block_footer = value;

        else if (variable == "license_path")
            configBuffer.license_path = value;

        else if (variable == "header_text")
            configBuffer.header_texts.push_back(value);

        else if (variable == "footer_text")
            configBuffer.footer_texts.push_back(value);

        // Number type variables
        else if (variable == "space_between_header_footer")
        {
            const int num = StringTools::string_to_int(std::string(value));
            configBuffer.space_between_header_footer = num;
        }

        else
        {
            // TODO: throw error : variable not match with knowned variable
        }
    }

    for (auto field : section.fields)
    {
        configBuffer.fields.push_back(field.get_value());
    }
}

auto Config::validation_config_buffer() -> void
{
    // Dependecy validation
    // We have 3 mother variable that if it wasn't get set other variable(Some of config options) -
    // can't be set
    // 1. comment         -> this variable need this mother variable "block_*, line_*, comment_style] varaibles"
    // 2. include_license -> this variable need this mother variable "license_path, include_license_before_header"
    if (configBuffer.comment == YES)
    {
        if (configBuffer.comment_style == YES)
        {
            if (configBuffer.block_header == "")
            {
                // TODO: throw error. write all block element
            }
            if (configBuffer.block_footer == "")
            {
                // TODO: throw error. write all block element
            }
            if (configBuffer.block_line_prefix == "")
            {
                // TODO: throw error. write all block element
            }
        }
        if (configBuffer.comment_style == NO)
        {
            if (configBuffer.line_prefix == "")
            {
                // TODO: throw error. write line prefix if you want to write your text in comment
            }
        }
    }
    else if (configBuffer.comment == NO)
    {
        if (configBuffer.comment_style == YES)
        {
            // TODO: warn not gonna get use
        }
    }

    else if (configBuffer.include_license == NO)
    {
        if (!configBuffer.license_path.empty())
        {
            // TODO: warn not gonna get use
        }
        if (configBuffer.include_license_before_header)
        {
            // TODO: warn not gonna get use
        }
    }
}
