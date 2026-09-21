#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <cstddef>
#include <filesystem>
#include <optional>
#include <variant>
#include <vector>

#include "buffer.hpp"
#include "macro.h"
#include "section.hpp"

using secbuf_sec_bool_t = std::variant<SectionBuffer, Section, bool>;

namespace Search
{
auto base_project_dir() -> std::optional<fs::path>;
auto project_config_path() -> fs::path;
secbuf_sec_bool_t storge_or_section(const std::vector<SectionBuffer> &section_buffers,
                                    const std::vector<Section> &sectios, std::string filename) noexcept;

/* Bool for std::vector<T> element existes.*/
template <typename T> auto if_element_exist(std::vector<T> vec, const unsigned int element_num) -> bool
{
    if (element_num < 0)
        return NO;

    return static_cast<size_t>(element_num) < vec.size();
}

} // namespace Search

#endif
