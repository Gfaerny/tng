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
[[nodiscard]] auto base_project_dir() -> std::optional<fs::path>;
[[nodiscard]] auto project_config_path() -> fs::path;

secbuf_sec_bool_t storge_or_section(
    const std::vector<SectionBuffer> &section_buffers,
    const std::vector<Section> &sectios, std::string filename) noexcept;

/* Bool for std::vector<T> or element existes.*/
template <typename T>
[[nodiscard]] auto if_element_exist(const std::vector<T> &vec,
                                    const size_t element_num) noexcept -> bool
{
    return element_num < vec.size();
}

[[nodiscard]] inline auto if_element_exist(const std::string &str,
                                           const size_t element_num) noexcept
    -> bool
{
    return element_num < str.size();
}

} // namespace Search

#endif
