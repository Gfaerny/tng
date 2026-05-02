#include "../include/tng_make_file.hpp"
#include <stdexcept>

/**
 * Return basic_string of file name extension string
 * like: file.cpp -> "cpp" , file.extension -> "extension" , file_no_extension
 * -> file_no_extension
 */
std::basic_string<char> extension_type(const std::string &filename)
{
    std::basic_string<char> file_extension_name = {""};
    for (char it : filename)
    {
        if (it != '.')
        {
            file_extension_name += it;
        }
        else if (it == '.')
        {
            if (file_extension_name != "")
                file_extension_name = "";
        }
    }
    return file_extension_name;
}

/**
 * Creat normal file using name_string vector list
 * This function exist to creat empty file and may used by other write_file*
 * functoin's
 */
void write_file(std::vector<std::string> &file_name)
{
    for (std::string r : file_name)
    {
        std::ofstream files;

        files.open(r);
        if (!files.is_open())
        {
            std::printf("tng error : File %s can't get created.\n check "
                        "directory or user permisions",
                        r.c_str());
            EXIT_FAILURE;
        }
        files.close();
    }
    return;
}

/**
 * Write license file
 */
void write_file_license(const std::vector<std::string> &filename, const std::string &license_filename)
{
    std::string license_file_path = "/usr/share/common-licenses/" + license_filename;

    if (!std::filesystem::exists(license_file_path))
    {
        std::printf("tng error : License file name (%s) could not find.\n", license_file_path.c_str());
        EXIT_FAILURE;
    }

    std::ifstream license_stream_obj(license_file_path);

    if (!license_stream_obj.is_open())
    {
        std::printf("tng error : tng can't open license file for streaming\ncheck"
                    "license exist in common_license or check user permision\n");
        EXIT_FAILURE;
    }

    write_file(filename);
    std::filebuf *license_stream_buffer = license_stream_obj.rdbuf();
    std::ofstream ofr;

    for (std::string r : filename)
    {
        ofr.open(r);

        // Error if input file didn't got created or we have issue in opening
        // input file
        if (!ofr.is_open())
        {
            std::printf("tng error : Can't write license in %s", r.c_str());
            EXIT_FAILURE;
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
/**
 * Write comment to file from config
 */
void write_file_config(const std::vector<std::string> &vector_filename, const std::string *config_filename,
                       const std::string &extension_filename)
{
    try
    {
        config Config;
        Config.load(config_path);
        for (std::string r : vector_filename)
        {
            if (Config.use_newline_for_multi_line == YES)
            {
            }
            if (Config.add_text == YES)
            {
            }
            // Here we have to use Config class
        }
    }
    catch (std::runtime_error &error)
    {
    }
}
/**
 * Main creating file's function
 * We use this function for call all tng_make_file function effencitevly
 */
void tng_make_file(const std::vector<std::string> &arguments, const std::string *config_filename,
                   const std::string *license_filename)
{
    std::ofstream files;
    if (config_filename == nullptr)
    {
        if (license_filename == nullptr)
        {
            write_file(arguments);
            EXIT_SUCCESS;
        }

        else
        {
            write_file(arguments);
            write_file_license(arguments, *license_filename);
            EXIT_SUCCESS;
        }
    }

    write_file(arguments);
    write_file_license(arguments, *license_filename);

    return;
}
/// now here we have to write all file with both config  config true ; license
/// = true;
