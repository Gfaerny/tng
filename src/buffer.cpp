#include <optional>

#include "buffer.hpp"

auto SectionBuffer::reset() -> void
{
    this->comment = std::nullopt;
    this->comment_style = std::nullopt;
    this->overwrite_existing_file = std::nullopt;

    this->line_prefix = "";
    this->block_header = "";
    this->block_line_prefix = "";
    this->block_footer = "";
    this->license_path = "";
    this->header_text = "";
    this->file_introduce = "";
    this->time_introduce = "";
    this->license_introduce = "";
    this->footer_text = "";
}
