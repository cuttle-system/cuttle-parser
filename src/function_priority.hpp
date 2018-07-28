#pragma once

#include <vector>
#include <string>
#include "function_id.hpp"

namespace cuttle {
	using function_priority_t = unsigned int;

	const function_priority_t FUNCTION_PRIORITY_ERROR = 0;
	const function_priority_t FUNCTION_PRIORITY_UNKNOWN = 1;
	const function_priority_t FUNCTION_PRIORITY_LAST = 2;
	const function_priority_t FUNCTION_PRIORITY_START = 3;

	struct function_priority_elem_t {
		function_id_t prev;
		function_priority_t prior;
		function_id_t next;
	};

	using function_priorities_t = std::vector<function_priority_elem_t>;
	
	struct function_priority_table_t {
		function_priorities_t priors;
	};
}