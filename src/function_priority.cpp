#include <tuple>
#include "function_priority.hpp"

cuttle::function_priority_t add(
	cuttle::function_priority_table_t &func_priors,
	cuttle::function_id_t func, cuttle::function_id_t after, cuttle::function_priority_t prior = FUNCTION_PRIORITY_UNKNOWN
) {
	using namespace cuttle;

	function_id_t next;

	
	if (after == FUNCTION_ID_UNKNOWN) {
		prior = 0;
	}

	func_priors.priors[func].prior = prior;
	func_priors.priors[func]

	while (next != FUNCTION_PRIORITY_UNKNOWN) {
		next = func_priors.priors[after].next
	}

	func_priors.priors[after].next = func;
}