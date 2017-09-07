#include <vector>
#include <string>
#include "parser.hpp"
#include "call_tree.hpp"
#include "context.hpp"
#include "token.hpp"

inline void parse_function_call(
	const husky::tokens_t& tokens, husky::call_tree_t& tree, husky::context_t& context, int &i,
	husky::funcs_t::const_iterator& it, int before = 0
) {
	using namespace husky;

	const function_t& func = it->second;
	tree.src.push_back({ i });
	int func_i = i;
	int func_tree_i = tree.src.size();
	if (func.type == PREFIX_FUNCTION) {
		for (int i = 0; i < func.args_number; ++i) {

		}
	}
	// TODO
	//INFIX_FUNCTION,
	//POSTFIX_FUNCTION,
	//POST_PREFIX_FUNCTION
}

void husky::parse(const tokens_t& tokens, call_tree_t& tree, context_t& context) {
	using namespace husky;

	int i = 0, i_default = 0;
	for (; i < tokens.size(); ++i) {
		const token_t& token = tokens[i];
		funcs_t::const_iterator& it = context.funcs.find(token.value);
		if (it != context.funcs.end()) {
			parse_function_call(tokens, tree, context, i_default, it, i);
			break;
		}
	}
}