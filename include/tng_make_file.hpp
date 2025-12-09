#pragma once
#include <vector>
#include <string>
#include <print>
#include <pwd.h>
#include <filesystem>
#include <fstream>
#include <streambuf>

#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>


void tng_make_file(const std::vector<std::string> , const bool TNG_CONFIG , const bool TNG_LICENSE);
