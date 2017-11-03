#pragma once

#include <unordered_map>
#include "function.hpp"
#include "function_priority.hpp"

namespace cuttle {
	using funcs_t = std::unordered_map<std::string, function_t>;
    typedef struct context {
        funcs_t funcs;
		function_priority_table_t funcs_prior;
    } context_t;
}