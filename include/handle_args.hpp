#pragma once

#include <cerrno>
#include <csignal>
#include <iostream>
#include <stdatomic.h>
#include <vector>
#include <cstdio>
#define texit return 0;


int handle_args( std::vector<std::string> tng_args_vec);
