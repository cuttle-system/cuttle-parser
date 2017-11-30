#pragma once

#include "function_priority.hpp"

namespace cuttle {
	void initialize(function_priority_table_t &func_priors);

	function_priority_t add(
		function_priority_table_t &func_priors, function_id_t func, function_id_t after
	);

	bool operator==(const function_priority_elem_t &left, const function_priority_elem_t &right);
	bool operator==(const function_priority_table_t &left, const function_priority_table_t &right);
}