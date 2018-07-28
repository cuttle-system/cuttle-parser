#pragma once

#include "context.hpp"

namespace cuttle {
	void initialize(context_t &context);
	void initialize(funcs_t &funcs);

	void add(context_t &context, const std::string& name, function_t func, function_id_t after);
	function_id_t add(funcs_t &funcs, funcname_to_id_t &funcname_to_id, std::string name, function_t func);
}