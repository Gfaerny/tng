#ifndef HANDLE_ARGS_H
#define HANDLE_ARGS_H

#include <string>
#include <vector>

#include "macro.h"

static auto expand_tilde(const fs::path &input_path) -> fs::path;
auto resolve_to_absolute(const fs::path &raw_path) -> fs::path;
auto handle_file(std::vector<std::string> file_explanations) -> std::vector<fs::path>;
auto handle_args(std::vector<std::string> &tng_args_vec) -> void;

#endif
