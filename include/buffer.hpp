#pragma once

#include <optional>
#include <string>
#include <vector>

#include "macro.h"

struct SectionBuffer
{
    std::vector<std::string> fields{};
    std::optional<bool> comment = std::nullopt;

    // `comment_style` vairable get filled in config file with `block` or `line` option
    // and in this buffer comment_style in order can be {YES} -> `block` and {NO} -> `line`
    std::optional<bool> comment_style;
    std::optional<bool> overwrite_existing_file;
    std::string_view line_prefix{""};
    std::string_view block_header{""};
    std::string_view block_line_prefix{""};
    std::string_view block_footer{""};
    std::string license_path{""};

    // preconfiged
    int space_between_header_footer{4};
    bool include_license_before_header{YES};

    // Layout
    // TODO: check if don't need use _view sufrix for layout value
    std::string header_text{""};
    std::string file_introduce{""};
    std::string time_introduce{""};
    std::string license_introduce{""};
    std::string footer_text{""};

    auto reset() -> void;
};
