#include <filesystem>
#include <iostream>
#include <vector>

#include "config.hpp"
#include "error.hpp"
#include "handle_args.hpp"
#include "macro.h"
#include "search.hpp"
#include "tng_make_file.hpp"

static auto expand_tilde(const fs::path &input_path) -> fs::path
{
    std::string path_str = input_path.string();

    if (path_str.empty() || path_str [0] != '~')
        return input_path;

    if (path_str.size() == 1 || path_str [1] == '/')
    {
        const char *home_env = std::getenv("HOME");
        fs::path home_dir;

        if (home_env != nullptr && home_env [0] != '\0')
        {
            home_dir = home_env;
        }
        else
        {
            /* Fallback to passwd database.  */
            struct passwd *pw = getpwuid(getuid());
            if (pw != nullptr && pw->pw_dir != nullptr)
                home_dir = pw->pw_dir;
            else
                return input_path; /* Cannot resolve home directory.  */
        }

        if (path_str.size() == 1)
            return home_dir;

        return home_dir / path_str.substr(2);
    }

    /* Handling ~otheruser/path expansion if required.  */
    std::size_t slash_pos = path_str.find('/');
    std::string username = (slash_pos == std::string::npos) ? path_str.substr(1) : path_str.substr(1, slash_pos - 1);

    struct passwd *pw = getpwnam(username.c_str());
    if (pw == nullptr || pw->pw_dir == nullptr)
        return input_path;

    fs::path result = pw->pw_dir;
    if (slash_pos != std::string::npos)
        result /= path_str.substr(slash_pos + 1);

    return result;
}

auto resolve_to_absolute(const fs::path &raw_path) -> fs::path
{
    fs::path expanded = expand_tilde(raw_path);
    std::error_code ec;
    fs::path canonical_path = fs::weakly_canonical(expanded, ec);

    if (ec)
    {
        if (expanded.is_relative())
            expanded = fs::current_path() / expanded;
        return expanded.lexically_normal();
    }

    return canonical_path;
}

auto handle_file(std::vector<std::string> file_explanations) -> std::vector<fs::path>
{
    std::vector<fs::path> return_vector{};
    for (std::string file_explanation : file_explanations)
    {
        fs::path resloved = resolve_to_absolute(file_explanation);
        return_vector.push_back(resloved);
    }
    return return_vector;
}

auto handle_args(std::vector<std::string> &tng_args_vec) -> void
{
    std::vector<std::string> files_path{};
    size_t iit = 0;
    bool config_called{NO};

    // Remove tng first argument element "./TNG_DIRECTORY/tng" or "tng"
    tng_args_vec.erase(tng_args_vec.begin());

    for (auto arg : tng_args_vec)
    {
        ++iit;

        // Help
        if (arg == "-h" || arg == "--help")
        {
            std::printf("tng Usage : tng -[OPTIONS] [FILENAME]"
                        "\n\n\n"
                        "-c [FILEPATH], --config [FILEPATH] :   locate config file path"
                        "\n\n"
                        "-h. --help    :   print help");
            return;
        }

        // Config
        else if (arg == "-c" || arg == "--config")
        {
            // Is next argument exist?
            if (!Search::if_element_exist(tng_args_vec, iit))
            {
                std::printf("tng error : No config file selected\nuse --help or -h option's to see usage");
                throw tng_error{.error_type_o = error_type::c_no_config_file_select, .error_massage = {}};
            }
            else if (config_called == YES)
            {
                std::printf("tng error : You can't address cofing file more then one time per command");
                throw tng_error{.error_type_o = error_type::c_cant_select_multi_conf, .error_massage = {}};
            }
            // TODO: need to change way of validate next argument in vector stack
            else
            {
                config_called = YES;
                // Set config_path global variable to new
                config_path = resolve_to_absolute(tng_args_vec [iit]);
            }
        }

        // Verbose
        else if (arg == "-v" || arg == "--verbose")
        {
            verbose = YES;
        }

        // Check for non-aviable options in argument vector
        //
        // for one char flag -> "-X"
        else if ((arg.size() == 2 && arg [0] == '-') || (arg.size() >= 2 && arg [0] == '-' && arg [1] == '-'))
        {
            // TODO: throw error : none active option flag got used. this flag option dosent exist.
        }

        else
        {
            files_path.push_back(tng_args_vec [iit]);
        }
    }

    tng_write_file(handle_file(files_path));
}
