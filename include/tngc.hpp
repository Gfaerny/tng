#pragma once
#include <fstream>

#include "config.hpp"
#include "macro.h"

enum class State
{
    none,
    reading_section_feild,
    reading_variable,

    reading_value,
    reading_value_string,
    reading_value_bool,
    reading_value_int,

    reading_section_between_feild
};

void read_set_tngc(Config::ConfigData &config_data);
