#pragma once

#include <string>
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <print>
#include <pwd.h>
#include <unistd.h>
#include <fstream>

#define YES true
#define NO false


passwd *pw = getpwuid(getuid());
char *c_style_home_dir = pw->pw_dir;
inline std::string home_dir_path = c_style_home_dir;
inline std::string config_path = home_dir_path + "/.config/tng/tng.conf";

bool use_newline_for_multi_line {};
bool add_text {};
std::vector <std::string> vec_license_dir_path ;
std::pair<std::vector<std::string>, std::vector<std::string>> extension_files_config_sepc;

class config
{
  public:
    int load(const std::string &config_path);
    ~config();
    void handle_error(const std::string& error_name);
    std::string clear_char_space(std::string &string);
    bool use_newline_for_multi_line {YES};
    bool add_text {NO};
    std::vector<std::string> vec_license_dir_path = {"/usr/sharer/common-license/"};
    std::pair<std::vector<std::string>, std::vector<std::string>> extension_files_config_spec;
};
