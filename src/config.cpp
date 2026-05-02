#include "../include/config.hpp"
#include <stdexcept>
/*
 * Remove space charecter from string
 * Except between '"' charecters
 */
std::string &config::clear_char_space(std::string &string)
{
    bool after_befor{NO};
    for (unsigned long i = 0; i < string.length(); ++i)
    {
        if (string[i] == ' ')
        {
            if (after_befor)
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
            after_befor = {YES};
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
        std::printf("tng error : config file do not exist -> %s", config_path.c_str());
        throw std::runtime_error("failed to open file");
    }
    // Print witch config now got loaded
    std::printf("tng alert : config that used -> %s", config_path.c_str());
    std::string line{""};
    std::string seprated_word{""};
    int line_number{0};
    while (std::getline(config_file, line))
    {
        line = clear_char_space(line);
        line_number += 1;

        if (line[0] == '#')
        {
            continue;
        }

        /// Now we seprate extension file specifiers with other varables
        else if (line.find("->"))
        {
            bool after_before{NO};
            std::string token{""};
            for (char r : line)
            {
                if (r == ',')
                {
                    if (!after_before)
                    {
                        extension_files_config_spec.first.push_back(token);
                    }
                    else
                    {
                        extension_files_config_spec.second.push_back(token);
                    }
                }
                else if (token == "->")
                {
                    after_before = true;
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

void config::handle_error(const std::string &error_name)
{
    if (error_name == "test")
    {
        throw std::runtime_error("test");
    }
}
