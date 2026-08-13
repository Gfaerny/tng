#include "../include/handle_args.hpp"
#include <vector>

uint16_t iit = 0;

bool license_called{NO}, config_called{NO};

auto handle_args(std::vector<std::string> &tng_args_vec) -> void
{
    for (auto it : tng_args_vec)
    {
        ++iit;
        // Help
        if (it == "-h" || it == "--help")
        {
            std::printf("tng usage : tng -[OPTIONS] [OPTION_CONFIG_NAME] [FILENAME]\n"

                        "-c    or    --config  :   use your writed config file for adding it to files that going to "
                        "created\n\n\n"
                        "-h    or    --help    :   use it to see this massage and tng gotta exit\n");
            return;
        }
        // Config
        else if (it == "-c" || it == "--config")
        {
            // Is next argument exist ?
            if (tng_args_vec.at(iit).empty())
            {
                std::printf("tng error : No config file selected\nuse --help or -h option's to see usage");
                throw tng_error{.error_type_o = error_type::c_no_config_file_select, .error_massage = {}};
            }
            else if (config_called == YES)
            {
                std::printf("tng error : You can't address cofing file more then one time per command");
                throw tng_error{.error_type_o = error_type::c_cant_select_multi_conf, .error_massage = {}};
            }
            else
            {
                // Remove argument contian config path and auto flag -> config
                tng_args_vec.erase(tng_args_vec.begin() + iit);
                tng_args_vec.erase(tng_args_vec.begin() + (iit + 1));
                config_called = YES;

                // Config_path is global var and it's effort config class when try to auto config -> load
                // TODO: write handler auto use -> for
                config_path = tng_args_vec[iit];
            }
        }
    }

    tng_make_file(std::move(tng_args_vec), &config_path);
}
