#include "../include/init.hpp"
#include <cstdlib>
/**
 * Initialize tng
 */
void init(int arg, char *argv[])
{
    // Getting arguments and write it to tng_args_vec
    std::vector<std::string> tng_args_vec;
    for (int i = 0; i < arg; ++i)
    {
        std::string argv_string = argv[i];
        tng_args_vec.push_back(argv_string);
    }

    // Pass tng_args_vec to handle_args function and handle exception
    try
    {
        handle_args(tng_args_vec);
    }
    catch (tng_error &e)
    {
        if (e.error_type == "EXPECT_ARGUMENT")
        {
            return;
        }
        else
        {
            return;
        }
    }
    return;
}
