#pragma once
#include <fstream>

#include "config.hpp"
#include "macro.h"

enum class State
{
    none,
    line_start,
    reading_section_feild,
    reading_section_between_feild,
    reading_variable,
    reading_value,
    reading_string_value,
    value_done,
    section_done
};

void read_set_tngc(ConfigData &config_data);
