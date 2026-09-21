#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

#include <optional>
#include <string>

namespace StringTools
{
auto extension_type(const std::string &filename) -> std::basic_string<char>;
auto clear_char_space(std::string &string) -> std::string;
auto after_until(const std::string &string, const char &after, const char &until) -> std::string;

template <typename T> T after_eqaul_value(std::string &line);

auto string_line_len(const std::string &string) -> std::optional<unsigned int>;
auto string_to_int(const std::string &string) -> int;
}; // namespace StringTools

#endif
