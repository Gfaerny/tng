#include <cstdio>
#include <filesystem>
#include <iostream>
#include <variant>

#include "buffer.hpp"
#include "config.hpp"
#include "error.hpp"
#include "macro.h"
#include "operator.hpp"
#include "search.hpp"
#include "section.hpp"
#include "tng_make_file.hpp"

using secbuf_sec_bool_t = std::variant<SectionBuffer, Section, bool>;

/*
 * Creat normal file using name_string auto list -> vector
 * porpuse of fucntion create empty file and may used by other write_file*
 * functoin's
 */
auto tng_write_file(const std::vector<fs::path> &files) -> void
{
    // When config obj get created
    // Config file in base project path or in system get selected and
    // 'tngc' parser get called, to fill buffer in 'Config' class

    Config config;

    /* Refer to configData object in class Config */
    auto &configData = config.configData;

    for (auto file : files)
    {
        secbuf_sec_bool_t storge_or_section =
            Search::storge_or_section(configData.sectionsBufferStorge, configData.sections, file);

        // There is no field that match for this filename in config file
        // TNG just create the file if it's not already exist
        if (const auto *boolean = std::get_if<bool>(&storge_or_section))
        {
            // TODO: Need to explain this functionallity to README
            // `tng` if file does not have any extension name choose filename
            // for example file named "hi" -> no extension, right! so tng choose hi as extension
            if (file.extension().empty())
                debug_prt("no field finded for this extension file name: %s", file.filename().c_str());
            else
                debug_prt("no field finded for this extension file name: %s", file.extension().c_str());
            // No config for this field. so we have to use wp manual argument passing
            WriteOperator wp(file, NO, YES);
            continue;
        }

        // finded field match in storged section buffer's
        else if (auto *buffer = std::get_if<SectionBuffer>(&storge_or_section))
        {
            debug_prt("find extension filename field in buffer: %s", file.extension().c_str());
            WriteOperator wp(file, *buffer, buffer->overwrite_existing_file);
            continue;
        }

        else if (auto *section = std::get_if<Section>(&storge_or_section))
        {
            config.fill_config_buffer(*section);
            config.validation_config_buffer();
            WriteOperator wp(file, config.configBuffer, config.configBuffer.overwrite_existing_file);

            // TODO: better to sync this order to on of the Config or Config.class
            // To push configBuffer to Config.Data.Storge
            config.configData.sectionsBufferStorge.push_back(config.configBuffer);
            config.configBuffer.reset();

            continue;
        }
    }
    return;
}
