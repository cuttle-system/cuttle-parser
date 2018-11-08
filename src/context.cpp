#include <utility>

#include <string>
#include "context_methods.hpp"
#include "function_priority_methods.hpp"

void cuttle::initialize(cuttle::context_t &context) {
	using namespace cuttle;

	initialize(context.funcs_prior);
	initialize(context.funcs);
    context.end_function_name.resize(3);
}

void cuttle::initialize(cuttle::funcs_t &funcs) {
	using namespace cuttle;

	function_t
		function_error = { function_type::prefix, 0 },
		function_unknown = { function_type::prefix, 0 },
		function_last = { function_type::prefix, 0 };

    funcs.resize(3);

	funcs[FUNCTION_ID_ERROR] = function_error;
	funcs[FUNCTION_ID_UNKNOWN] = function_unknown;
	funcs[FUNCTION_ID_LAST] = function_last;
}

void cuttle::add(cuttle::context_t &context, const std::string &name, cuttle::function_t func,
                 cuttle::function_id_t after,
                 std::string end_function_name) {
	using namespace cuttle;

	function_id_t id = add(context.funcs, context.funcname_to_id, name, func);
    context.end_function_name.push_back(std::move(end_function_name));
    add(context.funcs_prior, id, after);
}

cuttle::function_id_t cuttle::add(cuttle::funcs_t &funcs, cuttle::funcname_to_id_t &funcname_to_id, std::string name, cuttle::function_t func) {
    auto id = static_cast<function_id_t>(funcs.size());
	funcname_to_id[name] = id;
	funcs.push_back(func);
	return id;
}