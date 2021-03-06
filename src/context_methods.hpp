#pragma once

#include "context.hpp"

namespace cuttle {
	void initialize(context_t &context);
	void initialize(funcs_t &funcs);

	void add(cuttle::context_t &context, const std::string &name, cuttle::function_t func, cuttle::function_id_t after,
			 std::string end_function_name = "");
	function_id_t add(funcs_t &funcs, funcname_to_id_t &funcname_to_id, std::string name, function_t func);
}