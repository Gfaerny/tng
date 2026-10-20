#ifndef ERROR_H
#define ERROR_H

#include <string>

#define PRINT_LINE_COLUMN                                                      \
    std::to_string(line) + std::string(":") + std::to_string(column)

class tepic_error_massages
{
  public:
    /* ARGUMENT */
    /* ------------------------------------------------------------------- */
    /* Argument missing */
    inline static std::string ARG_EXPECT_MORE()
    {
        return "tng need more argument, check your used flag and there "
               "needs.\n If you use -c or --config flag."
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
        return option +
               " Does't supported yet.See -h or --help to see all flag options";
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
    inline static std::string TNGC_UNEXEC_COMMENT(const int line,
                                                  const int column)
    {
        return "Use comment sign ('#') in first of line." + PRINT_LINE_COLUMN;
    }

    inline static std::string TNGC_UNEXCEPT_SEC_DEF_ACT(const int line,
                                                        const int column)
    {
        return "Define a section after of before another section, Check (man "
               "tng.section)." +
               PRINT_LINE_COLUMN;
    }

    inline static std::string TNGC_UNEXEC_EQUEL(const int line,
                                                const int column)
    {
        return "Equal sign most used after after varibale defination. " +
               PRINT_LINE_COLUMN;
    };

    inline static std::string TNGC_UNEXEC_QUOTE(const int line,
                                                const int column)
    {
        return "Use \" charecter for define string line or multi-line."
               "\nExample:\n"
               "block_line_prefix = \" * \""
               "\nSee full example in tng.conf file.\n" +
               PRINT_LINE_COLUMN;
    };

    inline static std::string TNGC_UNCLOSE_ML_EQUEL(const int line,
                                                    const int column)
    {
        return "You should close your multi-line string with \"\"\"." +
               PRINT_LINE_COLUMN;
    };

    /* ------------------------------------------------------------------- */
};

struct tng_error
{
    const std::string error_massage;
};

#endif
