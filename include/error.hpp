#ifndef ERROR_H
#define ERROR_H

#include <cstdio>
#include <string>

enum class error_type
{
    cannot_open_create_file,
    expected_file_n_find,
    file_does_n_exist,

    arg_expected_argument,

    c_array_dn_more,
    c_more_less_symbol_EFNS,
    c_no_config_file_select,
    c_cant_select_multi_conf
};

class tepic_error_massages
{
  public:
    inline static std::string C_FILE_N_EXIST(const std::string &arg)
    {
        return "Your config file (" + arg + ") does not find.";
    }

    inline static std::string C_OPENING_FILE(const std::string &arg)
    {
        return "Config file can not be opened.\n"
               "Please see your current user premission status.\n"
               "Are you allow to open " +
               arg + " config file?";
    }
    inline static std::string C_FIND_FILE(const std::string &arg)
    {
        return "Your config file does not find." + arg;
    }
    inline static std::string C_ARRAY_DN_MORE(const std::string &arg)
    {
        return "You use '->' more then once in config file";
    }
};

struct tng_error
{
    error_type error_type_o;
    const std::string error_massage;
};

#endif
