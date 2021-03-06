#include "function_priority_methods.hpp"
#include "context_methods.hpp"
#include "invalid_function_id.hpp"

void cuttle::initialize(cuttle::function_priority_table_t &func_priors) {
	using namespace cuttle;
	func_priors.priors.resize(3);
	func_priors.priors[FUNCTION_ID_UNKNOWN] = function_priority_elem_t{ FUNCTION_PRIORITY_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR };
	func_priors.priors[FUNCTION_ID_UNKNOWN] = function_priority_elem_t{ FUNCTION_PRIORITY_ERROR, FUNCTION_PRIORITY_UNKNOWN, FUNCTION_ID_LAST };
	func_priors.priors[FUNCTION_ID_LAST] = function_priority_elem_t{ FUNCTION_PRIORITY_UNKNOWN, FUNCTION_PRIORITY_LAST, FUNCTION_PRIORITY_ERROR };
}

bool cuttle::operator==(const function_priority_elem_t &left, const function_priority_elem_t &right)
{
	return (left.prev == right.prev && left.prior == right.prior && left.next == right.next);
}

bool cuttle::operator==(const function_priority_table_t &left, const function_priority_table_t &right)
{
	return (left.priors == right.priors);
}

cuttle::function_priority_t cuttle::add(
	cuttle::function_priority_table_t &func_priors,
	cuttle::function_id_t func, cuttle::function_id_t after
) {
	using namespace cuttle;

    validate_function_id(func);
    validate_after_function_id(after);

	function_id_t next;
	function_priority_t prior;

	if (func >= func_priors.priors.size()) {
		func_priors.priors.resize(func + 1);
	}

	if (after == FUNCTION_ID_UNKNOWN) {
		prior = FUNCTION_PRIORITY_START;
	} else {
		prior = func_priors.priors[after].prior + 1;
	}

	next = func_priors.priors[after].next;

	func_priors.priors[func].prior = prior;
	func_priors.priors[func].prev = after;
	func_priors.priors[func].next = next;
	
	func_priors.priors[after].next = func;
	func_priors.priors[next].prev = func;

	for (; next != FUNCTION_ID_LAST; next = func_priors.priors[next].next) {
		++func_priors.priors[next].prior;
	}

	return prior;
}