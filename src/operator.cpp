#include <fstream>
#include <optional>
#include <sstream>
#include <streambuf>
#include <vector>

#include "operator.hpp"
#include "string_tools.hpp"

auto WriteOperator::import_text(const std::string &text) -> void
{
    std::vector<std::string> lines_header_text{};

    std::string line{};
    for (const auto &ch : text)
    {
        if (ch == '\n')
        {
            lines_header_text.push_back(line);
            line.clear();
        }
        line += ch;
    }

    if (section_buffer_copy.comment == YES)
    {
        if (section_buffer_copy.comment_style == YES)
        {
            if (lines_header_text.size() >= 3)
            {
                // seperate header_string by line and push to lines_header_text vector

                for (size_t iit = 0; iit - 2 < lines_header_text.size(); ++iit)
                {
                    if (iit == 1)
                    {
                        file_stream_copy << section_buffer_copy.block_header << '\n';
                    }
                    else if (static_cast<size_t>(iit + 1) == lines_header_text.size())
                    {
                        file_stream_copy << section_buffer_copy.block_footer << '\n';
                    }
                    else
                    {
                        file_stream_copy << section_buffer_copy.block_line_prefix << " " << lines_header_text[iit - 2]
                                         << '\n';
                    }
                }
            }
            else
            {
                // throw error: we need 3 or more line to use Block style
            }
        }
        else if (section_buffer_copy.comment_style == NO)
        {
            for (size_t iit = 0; iit < lines_header_text.size(); ++iit)
            {
                file_stream_copy << section_buffer_copy.line_prefix;
                file_stream_copy << lines_header_text[iit] << '\n';
            }
        }
    }

    else if (section_buffer_copy.comment == NO)
    {
        for (size_t iit = 0; iit < lines_header_text.size(); iit++)
        {
            file_stream_copy << lines_header_text[iit] << '\n';
        }
    }
}

auto WriteOperator::import_header_text() -> void
{
    import_text(section_buffer_copy.header_text);
}

auto WriteOperator::import_footer_text() -> void
{
    import_text(section_buffer_copy.footer_text);
}

auto WriteOperator::import_license_text() -> void
{
    std::fstream license_stream(section_buffer_copy.license_path);
    if (!license_stream.is_open())
    {
        // throw error : problem in opening license file
    }

    std::filebuf *lic_buf = license_stream.rdbuf();
    std::istream lic_stream(lic_buf);
    std::ostringstream oss;
    oss << lic_stream.rdbuf();
    const std::string license_string{oss.str()};

    import_text(license_string);
    license_stream.close();
}

WriteOperator::WriteOperator(std::fstream &file_stream, SectionBuffer &section_buffer)
{
    if (!file_stream.is_open())
    {
        // throw error
    }

    // Swap file stream ans section config buffer resource
    file_stream_copy.swap(file_stream);
    std::swap(section_buffer, section_buffer_copy);
}
