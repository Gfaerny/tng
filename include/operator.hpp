#ifndef OPERATOR_H
#define OPERATOR_H

#include <cstdio>
#include <fstream>
#include <optional>
#include <string_view>

#include "buffer.hpp"

class WriteOperator
{
  public:
    explicit WriteOperator(fs::path file, SectionBuffer &section_buffer, bool overwrite_file);
    explicit WriteOperator(fs::path file, bool overwrite_file);

    auto import_text(const std::string &text) -> void;
    auto import_header_text() -> void;
    auto import_license_text() -> void;
    auto import_footer_text() -> void;
    auto import_space_b_header_footer() -> void;

  private:
    SectionBuffer section_buffer{};
    std::fstream file_stream;
};

#endif
