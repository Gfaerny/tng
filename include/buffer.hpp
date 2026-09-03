#ifndef BUFFER_H
#define BUFFER_H

#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "macro.h"

struct SectionBuffer
{
    // `comment_style` vairable get filled in config file with `block` or `line` option
    // and in this buffer comment_style in order can be {YES} -> `block` and {NO} -> `line`

    std::vector<std::string_view> fields{};
    std::vector<std::string_view> header_texts{};
    std::vector<std::string_view> footer_texts{};

    std::optional<bool> comment = std::nullopt;
    std::optional<bool> comment_style;
    std::optional<bool> include_license;

    std::string_view line_prefix{""};
    std::string_view block_header{""};
    std::string_view block_line_prefix{""};
    std::string_view block_footer{""};
    std::string license_path{""};

    // preconfiged
    bool overwrite_existing_file{NO};
    int space_between_header_footer{4};
    bool include_license_before_header{YES};

    // Layout
    // TODO: check if don't need use _view sufrix for layout value

    auto reset() -> void;
};

#endif
