#include <cstddef>
#include <cstdlib>
#include <optional>
#include <sstream>

#include "buffer.hpp"
#include "macro.h"
#include "operator.hpp"

auto WriteOperator::import_text(const std::string &text) -> void
{
    std::vector<std::string> lines_header_text{};
    std::istringstream input(text);
    std::string line{};
    while (std::getline(input, line))
    {
        lines_header_text.push_back(line);
    }

    if (section_buffer.comment == YES)
    {
        if (section_buffer.comment_style == YES)
        {
            if (lines_header_text.size() >= 3)
            {
                // seperate header_string by line and push to lines_header_text vector
                file_stream << section_buffer.block_header << '\n';
                for (auto &line_input : lines_header_text)
                {
                    file_stream << section_buffer.block_line_prefix << " " << line_input << '\n';
                }
                file_stream << section_buffer.block_footer << '\n';
            }
            else
            {
                // throw error: we need 3 or more line to use Block style
            }
        }
        else if (section_buffer.comment_style == NO)
        {
            for (size_t iit = 0; iit < lines_header_text.size(); ++iit)
            {
                file_stream << section_buffer.line_prefix;
                file_stream << lines_header_text[iit] << '\n';
            }
        }
    }

    else if (section_buffer.comment == NO)
    {
        for (size_t iit = 0; iit < lines_header_text.size(); iit++)
        {
            file_stream << lines_header_text[iit] << '\n';
        }
    }
}

auto WriteOperator::import_header_text() -> void
{
    for (const auto &line : section_buffer.header_texts)
    {
        import_text(std::string(line));
    }
}

auto WriteOperator::import_footer_text() -> void
{
    for (const auto &line : section_buffer.footer_texts)
    {
        import_text(std::string(line));
    }
}

auto WriteOperator::import_license_text() -> void
{
    std::fstream license_stream(section_buffer.license_path);
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

auto WriteOperator::import_space_b_header_footer() -> void
{
    for (int count{0}; count < section_buffer.space_between_header_footer; count++)
    {
        import_text("\n");
    }
}

WriteOperator::WriteOperator(fs::path file, SectionBuffer &section_buffer, bool overwrite_file)
{
    if (overwrite_file)
        file_stream.open(file, std::ios::in | std::ios::out | std::ios::trunc);
    else
        file_stream.open(file, std::ios::in | std::ios::out);

    // Ask field config for add license before or not
    if (section_buffer.include_license_before_header)
        goto HEADER_FIRST;

    else
        goto LICENSE_FIRST;

HEADER_FIRST:
    import_header_text();
    import_license_text();
    import_space_b_header_footer();
    import_footer_text();
    goto END;

LICENSE_FIRST:
    import_license_text();
    import_header_text();
    import_space_b_header_footer();
    import_footer_text();

END:
    file_stream.close();
}
WriteOperator::WriteOperator(fs::path file, bool overwrite_file)
{
    if (overwrite_file)
        file_stream.open(file, std::ios::in | std::ios::out | std::ios::trunc);
    else
        file_stream.open(file, std::ios::in | std::ios::out);

    file_stream.close();
}
