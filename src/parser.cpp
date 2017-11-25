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

	if (tokens[i].type != ATOM_TOKEN) {
		return false;
	}

	funcname_to_id_t::const_iterator& it = context.funcname_to_id.find(tokens[i].value);
	if (it == context.funcname_to_id.end()) {
		return false;
	}

	function_id_t func_id = it->second;
	const function_t& func = context.funcs[func_id];
	int func_i = i;
	tree.src[i].resize(func.args_number);

	if (func.type == POSTFIX_FUNCTION || func.type == INFIX_FUNCTION) {
		if (prev == -1) {
			throw parse_error("'" + tokens[i].value + "' is a postfix function and recieves " + std::to_string(func.args_number) + " arguments");
		}
		// TODO if previous is a prefix function and is not fully parsed yet
		int argi = prev;
		int argi_prev = prev_prev;
		while (tree.src[argi].size() != 0) {
			function_id_t check_func_id;
			if (argi == tokens.size()) {
				check_func_id = FUNCTION_ID_UNKNOWN;
			}
			else {
				check_func_id = context.funcname_to_id[tokens[argi].value];
			}
			if (context.funcs_prior.priors[check_func_id].prior >= context.funcs_prior.priors[func_id].prior) {
				break;
			}
			if (context.funcs[check_func_id].type == POSTFIX_FUNCTION) {
				throw parse_error("'" + tokens[i].value + "' is a postfix function and recieves " + std::to_string(func.args_number) + " arguments");
			}
			argi_prev = argi;

			int j = 0;
			while (j < tree.src[argi].size() && tree.src[argi][j] != -1) ++j;
			if (j < 1) {
				throw parse_error("'" + tokens[i].value + "' is a postfix function and recieves " + std::to_string(func.args_number) + " arguments");
			}
			argi = tree.src[argi][j - 1];
		}
		tree.src[i][0] = argi;
		if (argi_prev != -1) {
			int j = 0;
			while (j < tree.src[argi_prev].size() && tree.src[argi_prev][j] != -1) ++j;
			if (j < 1) {
				throw parse_error("'" + tokens[i].value + "' is a postfix function and recieves " + std::to_string(func.args_number) + " arguments");
			}
			tree.src[argi_prev][j - 1] = i;
		}
		--before;
	}

	if (func.type == PREFIX_FUNCTION || func.type == INFIX_FUNCTION) {
		int j = i + 1;
		int argn = 0;
		if (func.type == INFIX_FUNCTION) {
			argn = 1;
		}
		for (; argn < func.args_number; ++argn, ++j) {
			if (j >= tokens.size()) throw parse_error("'" + tokens[i].value + "' recieves " + std::to_string(func.args_number) + " arguments");
			tree.src[i][argn] = -1;
			int saved_j = j;
			parse_function_call(tokens, tree, context, j, argn, i, prev);
			if (tree.src[i][argn] == -1) {
				tree.src[i][argn] = saved_j;
			}
		}
		i = j - 1;
	}

	return true;
}

void cuttle::parse(const tokens_t& tokens, call_tree_t& tree, context_t& context) {
	using namespace cuttle;

	int i = 0;
	int before = 0;
	tree.src.resize(tokens.size() + 1);
	auto& args = tree.src.back();
	int argn = 0;
	for (; i < tokens.size(); ++i, ++argn) {
		int saved_i = i;
		parse_function_call(tokens, tree, context, i, argn, tree.src.size() - 1);

		if (args.size() <= argn) {
			args.push_back(saved_i);
		}
		else {
			if (args[argn] != -1) continue;
			args[argn] = saved_i;
		}
	}
}