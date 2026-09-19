#ifndef MACRO_H
#define MACRO_H

#include <cstdio>
#include <filesystem>

constexpr bool YES = true;
constexpr bool NO = false;
namespace fs = std::filesystem;

/* Macro for priting debug info */
#define debug_prt(fmt, ...)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        if (verbose)                                                                                                   \
        {                                                                                                              \
            std::printf("tng verbose : " fmt, ##__VA_ARGS__);                                                          \
            std::printf("\n");                                                                                         \
        }                                                                                                              \
    } while (0)

#endif
