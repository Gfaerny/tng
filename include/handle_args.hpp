#pragma once

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <filesystem>
#include <vector>

#include "../include/config.hpp"
#include "../include/tng_make_file.hpp"

void handle_args(std::vector<std::string> tng_args_vec);

inline std::string license_filename{""};
