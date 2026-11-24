#ifndef OPERATOR_H
#define OPERATOR_H

#include <cstdio>
#include <fstream>
#include <optional>
#include <string_view>

#include "buffer.hpp"
#include "config.hpp"

class WriteOperator
{
  public:
    // TODO: re design WriteOperator class
    explicit WriteOperator(Config &cnf);
    explicit WriteOperator(fs::path file, SectionBuffer &section_buffer,
                           bool overwrite_file);
    explicit WriteOperator(fs::path file, bool overwrite_file,
                           std::optional<bool> create_non_exist_file);
    // TODO: We have to change this method arg and include options needed
    explicit WriteOperator(const fs::path file);

  private:
    auto import_text(const std::string &text) -> void;
    auto import_header_text() -> void;
    auto import_license_text() -> void;
    auto import_footer_text() -> void;
    auto import_space_b_header_footer() -> void;
    std::fstream file_stream;
};

#endif
