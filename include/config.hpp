#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <pwd.h>
#include <unistd.h>
#include <vector>

#include "buffer.hpp"
#include "macro.h"
#include "search.hpp"
#include "section.hpp"

inline passwd *pw = getpwuid(getuid());
inline char *PWD = pw->pw_dir;

inline fs::path home_directory{std::string(PWD)};
inline fs::path config_path = Search::base_project_dir().value();

struct ConfigData
{
    int current_index{0};
    // All of config file gather around in sections vector
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

    Config();

    auto fill_config_buffer(const Section &section) -> void;
    auto validation_config_buffer() -> void;
};
#endif
