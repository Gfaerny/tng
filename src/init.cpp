#include <string_view>

#include "error.hpp"
#include "handle_args.hpp"
#include "init.hpp"

auto init(int arg, char *argv []) -> void
{
    std::vector<std::string_view> tng_args_vec;
    for (int i = 0; i < arg; ++i)
    {
        std::string_view argv_string = argv [i];
        tng_args_vec.push_back(argv_string);
    }

    try
    {
        HandleArgs
    }

    catch (tng_error &e)
    {
        std::printf("tng error : %s", e.error_massage.c_str());
        return;
    }
    return;
}
