#include <algorithm>
#include <fstream>
#include <optional>
#include <vector>

#include "buffer.hpp"
#include "config.hpp"
#include "macro.h"
#include "string_tools.hpp"
#include "tngc.hpp"

auto TokenValue::set_text(std::string txt) -> void
{
    text = txt;
}

auto TokenValue::set_metadata(MetaData md) -> void
{
    md.line = metadata.line;
    md.column = metadata.column;
}

auto TokenValue::get_value() const -> std::string
{
    return this->text;
}

auto TokenValue::get_metadata() const -> MetaData
{
    return metadata;
}

auto VariableValue::push_metadata(size_t line, size_t column, bool is_variable) -> void
{
    if (is_variable)
    {
        variable.metadata.line = line;
        variable.metadata.column = column;
    }
    else
    {
        value.metadata.line = line;
        value.metadata.column = column;
    }
}
MetaData VariableValue::get_metadata(bool is_variable) const
{
    if (is_variable)
        return variable.get_metadata();
    else
        return value.get_metadata();
}

std::string_view VariableValue::get_variable() const
{
    return variable.text;
}

std::string_view VariableValue::get_value() const
{
    return value.text;
}

auto Section::push_field(std::string fieldStr, size_t line, size_t column)
{
    fields.push_back({fieldStr, {line, column}});
}

auto Section::push_var_val(std::string variableOrvalue, bool is_variable, size_t line, size_t column) -> void
{
    if (is_variable)
    {
        variable_value.emplace_back();
        variable_value.back().variable.set_text(variableOrvalue);
        variable_value.back().variable.set_metadata({.line = line, .column = column});
    }
    else
    {
        if (variable_value.empty())
        {
            // throw error
        }
        variable_value.back().value.set_text(variableOrvalue);
        variable_value.back().value.set_metadata({.line = line, .column = column});
    }
}

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

        else if (variable == "block_header")
            configBuffer.block_header = value;

        else if (variable == "block_line_prefix")
            configBuffer.block_line_prefix = value;

        else if (variable == "block_footer")
            configBuffer.block_footer = value;

        else if (variable == "license_path")
            configBuffer.license_path = value;

        else if (variable == "header_text")
            configBuffer.header_text = value;

        else if (variable == "file_introduce")
            configBuffer.file_introduce = value;

        else if (variable == "time_introduce")
            configBuffer.time_introduce = value;

        else if (variable == "license_introduce")
            configBuffer.license_introduce = value;

        else if (variable == "footer_text")
            configBuffer.footer_text = value;
        else
        {
            // throw error : variable not match with knowned variable
        }
    }

    for (auto field : section.fields)
    {
        configBuffer.fields.push_back(field.get_value());
    }
}

auto Config::validation_config_buffer() -> void
{
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
            // warning
        }
    }
}

auto Config::write_config(const std::fstream &file_stream, const std::string_view &file_name) -> void
{
    // TODO: we have to use this loop when if readed config section buffer vector is empty
    if (!configData.sectionsBufferStorge.empty())
    {
        for (auto buffer : configData.sectionsBufferStorge)
        {
        }
    }
    else
    {
        for (auto section : configData.section)
        {
            std::ranges::sort(section.fields, {}, &TokenValue::text);
            const bool found = std::ranges::binary_search(section.fields, file_name, {}, &TokenValue::text);

            if (found)
            {
                fill_config_buffer(section);
                validation_config_buffer();

                configBuffer.reset();
            }

            // VERBOS_TS:
        }
    }
}
