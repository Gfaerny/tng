#include "../include/config.hpp"
#include "../include/tngc.hpp"

auto TokenValue::set_text(std::string txt) -> void
{
    text = txt;
}

auto TokenValue::set_metadata(MetaData md) -> void
{
    md.line = metadata.line;
    md.column = metadata.column;
}

MetaData TokenValue::get_metadata() const
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

template <typename T> void ConfigData::pushSectionElement(T SectionData, int *number)
{
    if (typeid(T) != typeid(std::vector<std::string>))
    {
        CountDataFilling++;
        FieldVec.push_back(SectionData);
    }

    // If SectionData type is not vector<string> so it's just string
    else
    {
        if (!FieldVec.empty())
            FieldVec.back().push_back(SectionData);
        else
            FieldVec.push_back(SectionData);
    }
}

void ConfigData::pushVarableElement(std::string Variable)
{
    VariableVec.push_back(Variable);
}

void ConfigData::pushValueElement(std::string Value)
{
    ValueVec.push_back(Value);
}
