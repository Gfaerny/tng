#include <cstdio>
#include <filesystem>
#include <pwd.h>
#include <string_view>
#include <unistd.h>
#include <vector>

#include "config.hpp"
#include "error.hpp"
#include "handle_args.hpp"
#include "macro.h"
#include "path.hpp"

auto HandleArgs::read_args() -> void
{
    // TODO: I'm not sure about this function the way that we parse the config
    // path with bool and continue is really sus
    bool wc{NO};
    for (auto arg : args_)
    {
        if (arg == "-h" || arg == "--help")
        {
            print_help();
            return;
        }

        if (wc)
        {
            if (valid(arg))
            {
                conf_path = arg;
                debug_prt("config file that consider: %s",
                          std::string(arg).c_str());
            }
            else
                throw tng_error{.error_massage =
                                    tepic_error_massages::C_FILE_N_EXIST(arg)};

            wc = NO;
        }

        else if (arg == "-c" || "--config")
        {
            if (wc == YES)
                throw tng_error{
                    .error_massage =
                        tepic_error_massages::ARG_USE_MORE_THEN_ONCE()};

            wc = YES;
            continue;
        }

        else if (arg == "-v" || arg == "--verbose")
            verbose = YES;

        else if (arg == "-n" || arg == "--no-conf")
            use_conf = NO;

        else
        {
            auto path = reslove_to_valid(arg);

            if (valid(path))
                throw tng_error{.error_massage = "Path is't exist"};

            files.push_back(path);
        }
    }
}

// TODO: valid method must be declare in path.[cpp , hpp]
[[nodiscard]] auto HandleArgs::valid(fs::path path) -> bool
{
    if (!fs::exists(path.parent_path()))
        return NO;

    return YES;
}

auto HandleArgs::print_help() -> void
{
    char help_inf [] =
        ""
        "tng usage : tng -[OPTIONS] [FILENAME]"
        "\n\n\n"
        "-c [FILEPATH], --config [FILEPATH] :   locate config file path"
        "\n\n"
        "-h,            --help              :   print help"
        ""
        "";

    std::printf("%s", help_inf);
}
