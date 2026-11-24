#include <string_view>

#include "error.hpp"
#include "init.hpp"
#include <tng.hpp>

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
        Tng tng(tng_args_vec);
    }

    catch (const tng_error &e)
    {
        std::printf("tng error : %s", e.error_massage.c_str());
        return;
    }
    return;
}
