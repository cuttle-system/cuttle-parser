#pragma once

#include <unordered_map>
#include "function.hpp"

namespace husky {
	using funcs_t = std::unordered_map<std::string, function_t>;
    typedef struct context {
        funcs_t funcs;
    } context_t;
}