##
cmake_minimum_required(VERSION 3.15)
project(tng VERSION 1.0.0
                        DESCRIPTION "CLI linux app for making customable programing porpuse file"
                        LANGUAGES CXX
                        )

add_executable(tng src/tng_make_file.cpp src/handle_args.cpp src/init.cpp src/main.cpp src/config.cpp)
target_compile_options(tng PRIVATE
  -Wall
  -Wextra
  -O2
)
