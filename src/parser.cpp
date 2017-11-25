#include <vector>
#include <string>
#include "parse_error.hpp"
#include "parser.hpp"
#include "call_tree.hpp"
#include "context.hpp"
#include "token.hpp"

inline int parse_function_call(
	const cuttle::tokens_t& tokens, cuttle::call_tree_t& tree, cuttle::context_t& context,
	int &i, int& before, int prev = -1, int prev_prev = -1
) {
	using namespace cuttle;

	funcname_to_id_t::const_iterator& it = context.funcname_to_id.find(tokens[i].value);
	if (it == context.funcname_to_id.end()) {
		++before;
		return false;
	}

	function_id_t func_id = it->second;
	const function_t& func = context.funcs[func_id];
	int func_i = i;
	tree.src[i].resize(func.args_number);
	if (func.type == PREFIX_FUNCTION) {
		int j = i + 1;
		for (int argn = 0; argn < func.args_number; ++argn, ++j) {
			if (j >= tokens.size()) throw parse_error("'" + tokens[i].value + "' recieves " + std::to_string(func.args_number) + " arguments");
			tree.src[i][argn] = j;
			parse_function_call(tokens, tree, context, j, before, ((argn > 1) ? tree.src), );
		}
		i = j - 1;
		++before;
	}
	else if (func.type == POSTFIX_FUNCTION) {
		if (prev == -1) {
			throw parse_error("'" + tokens[i].value + "' is postfix function and recieves " + std::to_string(func.args_number) + " arguments");
		}
		int argi = prev;
		int argi_prev = prev_prev;
		while (tree.src[argi].size() != 0) {
			function_id_t check_func_id = context.funcname_to_id[tokens[argi].value];
			if (context.funcs_prior.priors[check_func_id].prior > context.funcs_prior.priors[func_id].prior) {
				break;
			}
			argi_prev = argi;
			argi = tree.src[argi].back();
		}
		tree.src[i][0] = argi;
		if (argi_prev != -1) {
			;
		}
	}
	else if (func.type == INFIX_FUNCTION) {
		// TODO
		throw std::logic_error("no implemented");
	}

	return true;
}

void cuttle::parse(const tokens_t& tokens, call_tree_t& tree, context_t& context) {
	using namespace cuttle;

	int i = 0;
	int before = 0;
	tree.src.resize(tokens.size());
	for (; i < tokens.size(); ++i) {
		parse_function_call(tokens, tree, context, i, before);
	}
}