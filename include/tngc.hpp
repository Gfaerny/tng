#pragma once

#include "config.hpp"

enum class State
{
    none,
    line_start,
    reading_section_feild,
    reading_section_between_feild,
    reading_variable,
    reading_value,
    reading_string_value,
    reading_string_multi_line_value,
    value_string_done,
    value_string_multi_line_done,
    value_done,
    section_done
};

void read_set_tngc(ConfigData &config_data);
