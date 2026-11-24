#ifndef TNG_MAKE_FILE_H
#define TNG_MAKE_FILE_H

#include "config.hpp"
#include "handle_args.hpp"
#include "macro.h"
#include "operator.hpp"

#include <string_view>
#include <vector>

// auto tng_write_file(const std::vector<fs::path> &file_names) -> void;

class Tng : public HandleArgs
{
  public:
    Tng(const std::vector<std::string_view> args) : HandleArgs(args)
    {
        if (!use_conf)
        {
            for (auto file : files)
            {
                WriteOperator wp(file);
            }
        }

        else
        {
            Config cnf(conf_path);
            WriteOperator wp(cnf);
        }
    }

  private:
};

#endif
