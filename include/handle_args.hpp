#ifndef HANDLE_ARGS_H
#define HANDLE_ARGS_H

#include <string>
#include <vector>

#include "macro.h"

class HandleArgs
{
  public:
    explicit HandleArgs(std::vector<std::string_view> args) : args_(args)
    {
        read_args();
    }

  private:
    auto read_args() -> void;

    // Check the parent_path from exists */
    auto valid(fs::path path) -> bool;

    auto print_help() -> void;

    std::vector<std::string_view> args_;
    std::vector<fs::path> files;
    fs::path conf_path{};
};

#endif
