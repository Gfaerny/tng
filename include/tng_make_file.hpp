#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

void tng_make_file(const std::vector<std::string> , const bool TNG_CONFIG , const bool TNG_LICENSE);
