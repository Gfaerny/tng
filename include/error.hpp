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
    arg_non_ava_option,

    c_array_dn_more,
    c_more_less_symbol_EFNS,
    c_no_config_file_select,
    c_cant_select_multi_conf,
    c_non_except_comment_sign_use
};

class tepic_error_massages
{
  public:
    /* ARGUMENT */
    /* ------------------------------------------------------------------- */
    /* Argument missing */
    inline static std::string ARG_EXPECT_MORE()
    {
        return "tng need more argument, check your used flag and there needs.\n If you use -c or --config flag."
               "satisfied it with config path after it.\nSee more with -h.\n";
    }

    /* Argument flag use more then one time */
    inline static auto ARG_USE_MORE_THEN_ONCE() -> std::string
    {
        return "Flag option got used more then one time.";
    }

    /* Argument option does not support yet */
    inline static auto ARG_NON_AVA_OPT(const std::string &option) -> std::string
    {
        return option + " Does't supported yet.See -h or --help to see all flag options";
    }

    /* ------------------------------------------------------------------- */

    /* Config */
    /* ------------------------------------------------------------------- */
    /* Config file not exist */
    inline static std::string C_FILE_N_EXIST(const std::string &arg)
    {
        return "Your config file (" + arg + ") does not find.";
    }

    /* Config file can't be open */
    inline static std::string C_OPENING_FILE(const std::string &arg)
    {
        return "Config file can not be opened.\n"
               "see your current user premission status.\n"
               "Are you allow to open " +
               arg + " config file?";
    }

    /* Config file can't be find */
    inline static std::string C_FIND_FILE(const std::string &arg)
    {
        return "Your config file does not find." + arg;
    }

    /* ------------------------------------------------------------------- */

    /* TNGC */
    /* ------------------------------------------------------------------- */
    /* Comment sign must be used first of line */
    inline static std::string TNGC_UNEXEC_COMMENT_SIGN(const int line, const int column)
    {
        return "Use comment sign ('#') in first of line." + std::to_string(line) + std::string(":") +
               std::to_string(column);
    }

    inline static std::string TNGC_OPEN_SEC(const int line, const int column)
    {
        // START: This error massage should explain what happend in tngc:60
        return "Define a section after of before another section, Check (man tng.section)." + std::to_string(line) +
               std::string(":") + std::to_string(column);
    }

    inline static std::string TNGC_CLOSE_SECT(const int line, const int column)
    {
        return "Close section defination after section got defined our there is no section to define. " +
               std::to_string(line) + std::string(":") + std::to_string(column);
    }
};

struct tng_error
{
    error_type error_type_o;
    const std::string error_massage;
};

#endif
