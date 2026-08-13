#pragma once

#include <vector>

#include "error.hpp"

void write_file(std::vector<std::string> &file_name);

void write_file_license(const std::vector<std::string> &filename, std::string *license_filename);

void write_file_config(const std::vector<std::string> &vector_filename, const std::string *config,
                       const std::string extention_filename);
void tng_make_file(const std::vector<std::string> &arguments, const std::string *config_filename);
