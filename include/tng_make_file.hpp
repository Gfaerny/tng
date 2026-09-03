#ifndef TNG_MAKE_FILE_H
#define TNG_MAKE_FILE_H

#include "macro.h"

#include <string>
#include <vector>

auto tng_write_file(const std::vector<fs::path> &file_names) -> void;

#endif
