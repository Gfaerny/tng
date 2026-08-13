#include <algorithm>

#include "config.hpp"
#include "operator.hpp"
#include "tng_make_file.hpp"

/**
 * Creat normal file using name_string auto list -> vector
 * This function exist to creat empty file and may used by other write_file*
 * functoin's
 */
auto tng_write_file(const std::vector<std::string> &file_names) -> void
{
    Config config;
    std::fstream file_stream;

    // Refer to configData object in class Config
    auto &configData = config.configData;

    for (auto file : file_names)
    {
        // Open file stream with fstream with write and read access
        // TODO: we should add std::ios::trunc when config order here
        file_stream.open(file, std::ios::out | std::ios::in);

        if (!file_stream.is_open())
        {
            // TODO: need to remove prinf and use tng_error .error_massage
            std::printf("tng error : File %s can't get created.\n check "
                        "directory or user permisions",
                        file.c_str());
            throw tng_error{.error_type_o = error_type::cannot_open_create_file,
                            .error_massage = {"CANNOT_OPEN_CREAT_FILE"}};
        }

        if (!configData.sectionsBufferStorge.empty())
        {
            for (auto buffer : configData.sectionsBufferStorge)
            {
                std::sort(buffer.fields.begin(), buffer.fields.end());

                if (!std::binary_search(buffer.fields.begin(), buffer.fields.end(), file))
                    break;

                // In SectioBufferStorge we have section with field for filename
                else
                {
                    // Now we have to pass this finded SectionBuffer (is't come from SectionBufferStorge) to main
                    // operator function
                    // We don't need fill_config_buffer and validation it's already did
                    WriteOperator wp(file_stream, buffer);
                    break;
                }
            }
        }

        else
        {
            for (auto section : configData.sections)
            {
                std::ranges::sort(section.fields, {}, &TokenValue::text);
                const bool found = std::ranges::binary_search(section.fields, file, {}, &TokenValue::text);

                if (found)
                {
                    config.fill_config_buffer(section);
                    config.validation_config_buffer();
                    WriteOperator wp(file_stream, config.configBuffer);
                    config.configBuffer.reset();
                }

                // TODO: VERBOS_TS
            }
        }
    }

    file_stream.close();
    return;
}
