#include "../include/init.hpp"

auto init(int arg, char *argv[]) -> void
{

    std::vector<std::string> tng_args_vec;
    for (int i = 0; i < arg; ++i)
    {
        std::string argv_string = argv[i];
        tng_args_vec.push_back(argv_string);
    }

    try
    {
        handle_args(tng_args_vec);
    }
    catch (tng_error &e)
    {
        if (e.error_type_o == error_type::arg_expected_argument)
        {
            return;
        }
        return;
    }
    return;
}
