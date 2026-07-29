#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <print>
#include <pwd.h>
#include <random>
#include <regex>
#include <string>
#include <string_view>
#include <unistd.h>
#include <vector>

#include "error.hpp"
#include "macro.h"
#include "string_tools.hpp"

passwd *pw = getpwuid(getuid());
char *c_style_home_dir = pw->pw_dir;

inline std::string home_dir_path = c_style_home_dir;
inline std::string config_path = home_dir_path + "/.config/tng/tng.conf";

struct MetaData
{
    size_t line{}, column;
};

struct TokenValue
{
    std::string text{};
    MetaData metadata;

    auto set_text(std::string txt) -> void;
    auto set_metadata(MetaData md) -> void;

    MetaData get_metadata() const;
};

struct VariableValue
{
    TokenValue variable;
    TokenValue value;

    /*
     *
     */
    auto push_metadata(size_t line, size_t column, bool var_val) -> void;
    /*
     * return metadata if bool is 0 return variable.metadata
     */
    MetaData get_metadata(bool is_variable) const;
    std::string_view get_variable() const;
    std::string_view get_value() const;
};

struct Section
{
    std::vector<TokenValue> fields{};
    std::vector<VariableValue> variable_value{};

    /*
     * Push in order fields
     */
    auto push_field(const std::string fieldStr, const size_t line, const size_t column);

    /*
     * Push in order, variavble and value string with bool true or false value
     */
    auto push_var_val(const std::string variableOrvalue, const bool is_variable, const size_t line, const size_t column)
        -> void;
};

struct ConfigBuffer
{
    bool comment;
    // `comment_style` vairable get filled in config file with `block` or `line` option
    // and in this buffer comment_style in order can be {YES} -> `block` and {NO} -> `line`
    bool comment_style;
    std::string_view line_prefix{};
    std::string_view block_header{};
    std::string_view block_line_prefix{};
    std::string_view block_footer{};
    std::string license_path{};

    // Layout
    // TODO: check if don't need use _view sufrix for layout value
    std::string header_text{};
    std::string file_introduce{};
    std::string time_introduce{};
    std::string license_introduce{};
    std::string footer_text{};
};

struct ConfigData
{
    int current_index{0};
    std::vector<Section> section{};

    auto section_validation(ConfigBuffer configBuffer) -> void;
    auto push_variable_value(const std::string variable_value, bool is_variable, size_t line, size_t column) -> void;
    auto push_field(const std::string field, const size_t line, const size_t column) -> void;
};

class Config
{
  public:
    ConfigData configData;
    ConfigBuffer configBuffer;
    Config();

    auto config_section_validation(const Section &section) -> void;
    auto write_config(std::fstream fs, const std::string file_name) -> void;

  protected:
    // All values
};
