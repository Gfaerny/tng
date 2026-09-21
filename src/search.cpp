#include "search.hpp"

#include <algorithm>
#include <filesystem>
#include <optional>
#include <variant>
#include <vector>

#include "buffer.hpp"
#include "config.hpp"
#include "string_tools.hpp"

namespace fs = std::filesystem;

auto Search::base_project_dir() -> std::optional<fs::path>
{
    fs::path directory(fs::current_path());

    // Look for .git in the current directory and its parents.
    while (true)
    {
        const auto git_path{directory / ".git"};

        if (fs::exists(git_path))
            return directory;

        const auto parent{directory.parent_path()};

        if (parent == directory)
            break;

        // note finded
        if (directory == "/")
            break;

        directory = parent;
    }
    return std::nullopt;
}

auto Search::project_config_path() -> fs::path
{
    std::filesystem::path current_path = std::filesystem::current_path();
    fs::path default_config_file_path = home_directory() / ".config" / "tng" / "tng.conf";

    if (Search::base_project_dir() != std::nullopt)
    {
        if (fs::exists(Search::base_project_dir().value() / "tng.conf"))
        {
            return fs::path(home_directory() / ".config" / "tng" / "tng.conf");
        }
        config_path = Search::base_project_dir().value() / "tng.conf";
    }

    else if (!fs::exists(default_config_file_path))
    {
        // throw error : installing process must be wrong or not complete
    }

    return fs::path(home_directory() / ".config" / "tng" / "tng.conf");
}

// TODO: for files that ordered to create or passed to tng we need to hanlde them in struct with
// path and name

/*
 * This function search for sectionBuffer and it's storge in configData in Config and if it fit
 */
secbuf_sec_bool_t Search::storge_or_section(const std::vector<SectionBuffer> &section_buffers,
                                            const std::vector<Section> &sectios, std::string filename) noexcept
{
    for (auto buffer : section_buffers)
    {
        std::sort(buffer.fields.begin(), buffer.fields.end());
        if (std::binary_search(buffer.fields.begin(), buffer.fields.end(), filename) ||
            std::binary_search(buffer.fields.begin(), buffer.fields.end(), StringTools::extension_type(filename)))
        {
            return buffer;
        }
        // TODO: we have to sperate filename from file path in file_names cuz of
        // argument handling
        // for example : tng reza.cpp src/mamad.cpp
    }

    for (auto section : sectios)
    {
        std::ranges::sort(section.fields, {}, &TokenValue::text);
        if (std::ranges::binary_search(section.fields, filename, {}, &TokenValue::text) ||
            std::ranges::binary_search(section.fields, StringTools::extension_type(filename), {}, &TokenValue::text))
        {
            return section;
        }
    }

    return NO;
}
