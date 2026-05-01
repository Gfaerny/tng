#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <print>
#include <pwd.h>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#define YES true
#define NO false

passwd *pw = getpwuid(getuid());
char *c_style_home_dir = pw->pw_dir;
inline std::string home_dir_path = c_style_home_dir;
inline std::string config_path = home_dir_path + "/.config/tng/tng.conf";

class config
{
  public:
    ~config();
    // All config values
    bool use_newline_for_multi_line{YES};
    bool add_text{NO};
    int new_line_befor_comment{0};

    std::string &clear_char_space(std::string &string);
    std::vector<std::string> vec_license_dir_path = {"/usr/sharer/common-license/"};
    std::pair<std::vector<std::string>, std::vector<std::string>> extension_files_config_spec;

    void handle_error(const std::string &error_name);
    int load(const std::string &config_path);
};
