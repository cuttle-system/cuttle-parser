#pragma once

#include <unordered_map>
#include <string>
#include "function.hpp"

#define FUNCTION_PRIORITY_UNKNOWN -1

namespace cuttle {
	using function_priority_t = int;
	typedef struct function_priorities {
		std::unordered_map<std::string, function_priority_t> func_to_prior;
		std::unordered_map<function_priority_t, std::string> prior_to_func;
	} function_priorities_t;
	function_priority_t push(function_priorities_t &priors, function_priority_t prior, const std::string& func_name);
	function_priority_t push(
		const function_priorities_t &priors,
		const std::string& func_name, const std::string& func_name_before, const std::string& func_name_after
	);

	function_priority_t compare(const function_priorities_t &priors, const std::string& func_name1, const std::string& func_name2);
}