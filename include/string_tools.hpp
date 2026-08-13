#pragma once

#include <optional>
#include <string>

namespace StringTools
{
std::basic_string<char> extension_type(const std::string &filename);

std::string clear_char_space(std::string &string);

std::string after_until(const std::string &string, const char &after, const char &until);

template <typename T> T after_eqaul_value(std::string &line);

std::optional<int> string_line_len(const std::string &string);
}; // namespace StringTools
