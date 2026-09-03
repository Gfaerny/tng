##
cmake_minimum_required(VERSION 3.15)
project(tng VERSION 1.0.0
                        DESCRIPTION "CLI linux app for making customable programing porpuse file"
                        LANGUAGES CXX
                        )

add_executable(tng)

target_sources(tng
    PRIVATE
        src/init.cpp
        src/main.cpp
        src/tngc.cpp
        src/buffer.cpp
        src/config.cpp
        src/search.cpp
        src/section.cpp
        src/operator.cpp
        src/handle_args.cpp
        src/string_tools.cpp
        src/tng_make_file.cpp
)

target_include_directories(tng
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(tng PRIVATE
  -g3
  -O0
  -Wall
  -Wunused-but-set-parameter
  -Wextra
  -O2
  -std=c++20
)
