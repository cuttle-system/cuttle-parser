#pragma once

#include <unordered_map>
#include "function.hpp"

namespace husky {
    typedef struct context {
        std::unordered_map<std::string, function_t> funcs;
    } context_t;
}