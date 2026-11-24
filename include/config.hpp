#ifndef CONFIG_H
#define CONFIG_H
#include <filesystem>

#include "buffer.hpp"
#include "macro.h"
#include "section.hpp"

inline auto home_directory() -> fs::path
{
    char *home_env(std::getenv("HOME"));
    return fs::path(home_env);
}

inline bool verbose{NO};

// TODO: change ConfigData to class
struct ConfigData
{
    /* Current section index number */
    unsigned int current_index{0};

    // All of config file gather around in sections vector
    std::vector<Section> sections{};

    /* Collected Section with applied state in past */
    std::vector<SectionBuffer> sectionsBufferStorge{};

    auto section_validation(SectionBuffer configBuffer) -> void;

    auto push_variable_value(const std::string variable_value, bool is_variable,
                             size_t line, size_t column) -> void;
    /* Need std::string_view for first argument */
    auto push_field(const std::string &field, const size_t &line,
                    const size_t &column) -> void;
};

class Config
{
  public:
    explicit Config(const fs::path conf_path);
    friend class WriteOperator;

  private:
    ConfigData conf_data;
    SectionBuffer conf_buffer;

    auto fill_cnf_buffer(Section &section) -> void;
    auto valid_cnf_data() -> void;
};

#endif
