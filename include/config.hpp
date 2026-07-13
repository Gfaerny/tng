#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <print>
#include <pwd.h>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "error.hpp"
#include "macro.h"

passwd *pw = getpwuid(getuid());
char *c_style_home_dir = pw->pw_dir;
inline std::string home_dir_path = c_style_home_dir;
inline std::string config_path = home_dir_path + "/.config/tng/tng.conf";

class Config
{
  public:
    ~Config();

    // All config values
    bool use_newline_for_multi_line{YES}, add_text{NO}, use_symbol_between_multi_line{NO},
        import_license_with_comment{YES};

    int new_line_before_comment{0};

    std::vector<std::string> vec_license_dir_path = {"/usr/sharer/common-license/"};
    // vector that store line to line pair of extension filename and their specified comment charecter

    // TODO: we have to use constructor for load config

    int load(const std::string &config_path);
};

struct ConfigData
{
    std::vector<std::vector<std::string>> FieldVec{{}};
    std::vector<std::string> VariableVec{};
    std::vector<std::string> ValueVec{};

    template <typename T> void pushSectionElement(T SectionData, int *number);
    void pushVarableElement(std::string Variable);
    void pushValueElement(std::string Value);

    int CountDataFilling{0};
};
