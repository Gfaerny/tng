#pragma once

#include <cstdio>
#include <fstream>

#include "buffer.hpp"

class WriteOperator
{
  public:
    explicit WriteOperator(std::fstream &file_stream, SectionBuffer &section_buffer);

    auto import_text(const std::string &text) -> void;
    auto import_header_text() -> void;
    auto import_license_text() -> void;
    auto import_footer_text() -> void;

  private:
    SectionBuffer section_buffer_copy;
    std::fstream file_stream_copy;
    std::string line_comment_spec = {""};
};
