#include <optional>

#include "buffer.hpp"

auto SectionBuffer::reset() -> void
{
    this->fields.clear();
    this->header_texts.clear();
    this->footer_texts.clear();

    this->comment = NO;
    this->comment_style = NO;
    this->overwrite_existing_file = NO;
    this->include_license = NO;

    this->line_prefix = "";
    this->block_header = "";
    this->block_line_prefix = "";
    this->block_footer = "";
    this->license_path = "";
}
