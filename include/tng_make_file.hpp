#pragma once
#include <vector>
#include <string>
#include <print>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <streambuf>


void tng_make_file(const std::vector<std::string> , const bool TNG_CONFIG , const bool TNG_LICENSE);
