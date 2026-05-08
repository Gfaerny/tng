#include "../include/handle_args.hpp"

uint16_t iit = 0;

bool license_bool{NO}, config_bool{NO};

void handle_args(std::vector<std::string> &tng_args_vec)
{
    for (auto it : tng_args_vec)
    {
        ++iit;
        // Help
        if (it == "-h" || it == "--help")
        {
            std::printf(
                "tng usage : tng -[OPTIONS] [OPTION_CONFIG_NAME] [FILENAME]\n"

                "-c    or    --config  :   use your writed config's file for adding it to files that going to "
                "created\n\n\n"
                "-l    or    --license :   use you writted or available license for adding them to you file\n\n\n"
                "-h    or    --help    :   use it to see this massage and tng gotta exit\n");
            return;
        }
        // Config
        else if (it == "-c" || "--config")
        {
            // Is next argument exist ?
            if (tng_args_vec.at(iit).empty())
            {
                std::printf("tng error : No config file selected\nuse --help or -h option's to see usage");
                throw tng_error{.error_type = "EXPECT_ARGUMENT"};
            }
            else if (config_bool == YES)
            {
                std::printf("tng error : You can't address cofing file more then one time per command");
                throw tng_error{.error_type = "UNCORRECT_ARGUMENT_USE"};
            }
            else
            {
                tng_args_vec.erase(tng_args_vec.begin() + iit);
                config_bool = YES;

                // Config_path is global var and it's effort config class when try to load config
                config_path = tng_args_vec[iit];
            }
        }
        // License
        else if (it == "-l" || it == "--license")
        {
            if (tng_args_vec.at(iit).empty())
            {
                std::printf("tng error : No license file selected\nuse --help or -h option's for see usage");
                throw tng_error{.error_type = "EXPECT_ARGUMENT"};
            }
            else if (license_bool == YES)
            {
                std::printf("tng error : You can't address license file more then one time per command, but you  can "
                            "use .config file for setting license PATH's that can help you find you license when it is "
                            "not in this directory\n");
                throw tng_error{.error_type = "UNCORRECT_ARGUMENT_USE"};
            }
            else
            {
                license_filename = tng_args_vec[iit];
                tng_args_vec.erase(tng_args_vec.begin() + iit);
                license_bool = YES;
            }
        }
    }

    // Call tng_make_file for pass config_path and license_name
    if (config_bool && license_bool)
    {
        tng_make_file(tng_args_vec, &config_path, &license_filename);
    }
    else if (!config_bool && license_bool)
    {
        tng_make_file(tng_args_vec, NULL, &license_filename);
    }
    else
    {
        tng_make_file(tng_args_vec, NULL, NULL);
    }

    // We have license_filename
    // We have cofnig_path
    // We have all files name in tng_args_vec
    return;
}
