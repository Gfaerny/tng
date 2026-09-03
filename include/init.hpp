#ifndef INIT_H
#define INIT_H

#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <string_view>

#include "error.hpp"
#include "handle_args.hpp"

auto init(int arg, char *argv[]) -> void;

#endif
