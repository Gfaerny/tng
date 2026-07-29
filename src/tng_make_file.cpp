#include "../include/tng_make_file.hpp"

/**
 * Creat normal file using name_string auto list -> vector
 * This function exist to creat empty file and may used by other write_file*
 * functoin's
 */
auto tng_write_file(const std::vector<std::string> &file_names) -> void
{
    Config config;

    for (auto file : file_names)
    {
        std::fstream file_stream;

        file_stream.open(file, std::ios::out | std::ios::in);
        if (!file_stream.is_open())
        {
            std::printf("tng error : File %s can't get created.\n check "
                        "directory or user permisions",
                        file.c_str());
            throw tng_error{.error_type_o = error_type::cannot_open_create_file,
                            .error_massage = {"CANNOT_OPEN_CREAT_FILE"}};
        }

        config.write_config(std::move(file_stream), file);
        file_stream.close();
    }
    return;
}

/**
 * Write auto file -> license
 */
void write_file_license(const std::vector<std::string> &filename, const std::string &license_filename)
{
    std::string license_file_path = "/usr/share/common-licenses/" + license_filename;

    if (!std::filesystem::exists(license_file_path))
    {
        // TODO: need to remove prinf and use tng_error .error_massage
        std::printf("tng error : License file name (%s) could not find.\n", license_file_path.c_str());
        throw tng_error{.error_type_o = error_type::cannot_open_create_file,
                        .error_massage = {"LICENSE_FILE_CAN'T_FIND"}};
    }

    std::ifstream license_stream_obj(license_file_path);

    if (!license_stream_obj.is_open())
    {
        // TODO: need to remove prinf and use tng_error .error_massage
        std::printf("tng error : tng Can't open license file for streaming\ncheck"
                    "license exist in common_license or check user permision\n");
        throw tng_error{.error_type_o = error_type::cannot_open_create_file,
                        .error_massage = {"CANNOT_OPEN_CREAT_FILE"}};
    }

    std::filebuf *license_stream_buffer = license_stream_obj.rdbuf();
    std::ofstream ofr;

    for (std::string r : filename)
    {
        ofr.open(r);
        if (!ofr.is_open())
        {
            // TODO: need to remove prinf and use tng_error .error_massage
            std::printf("tng error : Can't write license in %s", r.c_str());
            throw tng_error{.error_type_o = error_type::cannot_open_create_file,
                            .error_massage = {"CANNOT_OPEN_CREAT_FILE"}};
        }

        std::filebuf *target_file_buffer = ofr.rdbuf();

        char license_filebuf_char_intr = license_stream_buffer->sbumpc();

        while (license_filebuf_char_intr != EOF)
        {
            target_file_buffer->sputc(license_filebuf_char_intr);
            license_filebuf_char_intr = license_stream_buffer->sbumpc();
        }
    }
    return;
}
