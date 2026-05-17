#include "../include/config.hpp"

#define RESET_TOKEN token = ""

/*
 * Remove space charecter from string
 * Except between '"' charecters
 */
std::string &config::clear_char_space(std::string &string)
{
    bool after_before{NO};
    for (unsigned long i = 0; i < string.length(); ++i)
    {
        if (string[i] == ' ')
        {
            if (after_before)
            {
                // Do nothing
            }
            else
            {
                string.erase(i, 1);
            }
        }
        else if (string[i] == '"')
        {
            after_before = {YES};
        }
    }
    return string;
}
/*
 * Config loader and config value setter
 */
int config::load(const std::string &config_path)
{
    // We first try to open config file
    // We want config file be hardcoded but also can changed by argument
    // Thet hardcoded address = $HOME/.config/tng/tng.conf but also can changed by --config or -c option
    // Check tng.conf config file
    std::ifstream config_file(config_path);
    if (!std::filesystem::exists(config_path))
    {
        std::printf("tng error : config file (%s), do not exist", config_path.c_str());
        throw tng_error{.error_type_o = error_type::file_does_n_exist,
                        .error_massage = tepic_error_massages::C_FILE_N_EXIST(config_path)};
    }
    // Print witch config now got loaded
    std::printf("tng alert : config that used -> %s", config_path.c_str());
    std::string line{""};
    std::string seprated_word{""};
    int line_number{0};
    // Each line that provide one of extension file comment charecter defination got counted by this varable
    int extension_file_spec_counter{0};
    while (std::getline(config_file, line))
    {
        clear_char_space(line);
        line_number += 1;

        if (line[0] == '#')
        {
            continue;
        }

        // Now we seprate extension file specifiers with other varables

        else if (line.find("->"))
        {
            extension_file_spec_counter += 1;
            // After mean YES before mean NO
            bool after_before{NO};

            std::string token{""};

            int char_number_in_line{0};
            for (char r : line)
            {
                char_number_in_line += 1;
                if (r == ',')
                {

                    if (!after_before)
                    {
                        extension_files_config_spec[extension_file_spec_counter].first.push_back(token);
                    }
                    else
                    {
                        extension_files_config_spec[extension_file_spec_counter].second.push_back(token);
                    }
                    // Reset token
                    RESET_TOKEN;
                }
                else if (token == "->")
                {
                    if (!after_before)
                        after_before = true;
                    // else mean when '->' array symbol got foregotet
                    else
                    {
                        throw tng_error{.error_type_o = error_type::c_array_dn_more,
                                        .error_massage = tepic_error_massages::C_ARRAY_DN_MORE("")};
                    }
                    RESET_TOKEN;
                }
                else
                {
                    token += r;
                }
            }
        }
        else
        {
            // Bool var config
            if (line.find("use_newline_for_multi_line"))
            {
                use_newline_for_multi_line = YES;
            }
            else if (line.find("license_path"))
            {
                // No option for now
            }
            // And gonna add more config option with bool utile
        }
    }

    return 0;
}
