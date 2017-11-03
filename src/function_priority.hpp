#pragma once

#include <vector>
#include <string>
#include "function.hpp"

#define FUNCTION_PRIORITY_UNKNOWN -1

namespace cuttle {
	using function_priority_t = int;
	typedef struct function_priority_elem {
		function_id_t prev;
		function_priority_t prior;
		function_id_t next;
	} function_priority_elem_t;
	typedef struct function_priority_table {
		std::vector<function_priority_elem_t> priors;
	} function_priority_table_t;

	function_priority_t add(
		function_priority_table_t &func_priors, function_id_t func, function_id_t after, function_priority_t prior
	);
}