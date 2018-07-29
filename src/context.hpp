#pragma once

#include <string>
#include <unordered_map>
#include "function.hpp"
#include "function_priority.hpp"
#include "function_id.hpp"

namespace cuttle {
	using funcname_to_id_t = std::unordered_map<std::string, function_id_t>;
	using funcs_t = std::vector<function_t>;

    struct context_t {
		funcname_to_id_t funcname_to_id;
		funcs_t funcs;
		function_priority_table_t funcs_prior;
    };
}