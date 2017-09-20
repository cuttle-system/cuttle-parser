#include <vector>
#include <string>
#include "parse_error.hpp"
#include "parser.hpp"
#include "call_tree.hpp"
#include "context.hpp"
#include "token.hpp"

inline int parse_function_call(
	const husky::tokens_t& tokens, husky::call_tree_t& tree, husky::context_t& context,
	int &i, int& before
) {
	using namespace husky;

	funcs_t::const_iterator& it = context.funcs.find(tokens[i].value);
	if (it == context.funcs.end()) {
		++before;
		return false;
	}

	const function_t& func = it->second;
	int func_i = i;
	int j = i + 1;
	tree.src[i].resize(func.args_number);
	if (func.type == PREFIX_FUNCTION) {
		for (int argn = 0; argn < func.args_number; ++argn, ++j) {
			if (j >= tokens.size()) throw parse_error("'" + tokens[i].value + "' recieves " + std::to_string(func.args_number) + " arguments");
			tree.src[i][argn] = j;
			parse_function_call(tokens, tree, context, j, before);
		}
	}
	// TODO
	//INFIX_FUNCTION,
	//POSTFIX_FUNCTION,
	//POST_PREFIX_FUNCTION
	i = j - 1;

	++before;

	return true;
}

void husky::parse(const tokens_t& tokens, call_tree_t& tree, context_t& context) {
	using namespace husky;

	int i = 0;
	int before = 0;
	tree.src.resize(tokens.size());
	for (; i < tokens.size(); ++i) {
		parse_function_call(tokens, tree, context, i, before);
	}
}