#pragma once

#include <cerrno>
#include <csignal>
#include <vector>
#include <cstdio>
#include <filesystem>

#include "../include/tng_make_file.hpp"
#include "../include/config.hpp"

void handle_args( std::vector<std::string> tng_args_vec);

inline std::string license_filename {""};
