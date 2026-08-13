#pragma once

#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <vector>

#include "buffer.hpp"

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

    auto get_metadata() const -> MetaData;
    auto get_value() const -> std::string;
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

struct ConfigData
{
    int current_index{0};
    std::vector<Section> sections{};
    std::vector<SectionBuffer> sectionsBufferStorge{};

    auto section_validation(SectionBuffer configBuffer) -> void;
    auto push_variable_value(const std::string variable_value, bool is_variable, size_t line, size_t column) -> void;
    auto push_field(const std::string &field, const size_t &line, const size_t &column) -> void;
};

class Config
{
  public:
    ConfigData configData;
    SectionBuffer configBuffer;
    std::vector<SectionBuffer> readed_config_section_buffer;

    Config();

    auto fill_config_buffer(const Section &section) -> void;
    auto validation_config_buffer() -> void;
    auto write_config(const std::fstream &file_stream, const std::string_view &file_name) -> void;

  protected:
    // All values
};
