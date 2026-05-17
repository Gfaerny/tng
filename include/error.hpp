#pragma once

#include <cstdio>
#include <string>

enum class error_type
{
    cannot_open_creat_file,
    expected_file_n_find,
    file_does_n_exist,
    // Config error tpyes
    c_array_dn_more
};

// tepic_error_massage struct try to help us for better error and bug handling
// for both user and developer
class tepic_error_massages
{
  public:

    inline static std::string C_FILE_N_EXIST(const std::string &arg)
    {
        return "Your config file (" + arg + ") does not find.";
    }
    // Error when
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
    // const std::string error_type{} this string object must need for config file errors
    const std::string error_massage;
    // It's possible to add file class object for closing resource of file's
};
