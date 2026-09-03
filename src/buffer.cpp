#include <optional>

#include "buffer.hpp"

auto SectionBuffer::reset() -> void
{
    this->fields.clear();
    this->header_texts.clear();
    this->footer_texts.clear();

    this->comment = std::nullopt;
    this->comment_style = std::nullopt;
    this->overwrite_existing_file = std::nullopt;
    this->include_license = std::nullopt;

    this->line_prefix = "";
    this->block_header = "";
    this->block_line_prefix = "";
    this->block_footer = "";
    this->license_path = "";
}
