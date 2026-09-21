#include "section.hpp"

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

auto Section::push_field(std::string fieldStr, size_t line, size_t column) -> void
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
