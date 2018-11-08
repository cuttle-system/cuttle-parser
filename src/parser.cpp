#include <vector>
#include <string>
#include <list>
#include <stack>
#include <algorithm>
#include "parse_error.hpp"
#include "parser.hpp"

inline int parse_function_call(
		const cuttle::tokens_t &tokens, cuttle::call_tree_t &tree, cuttle::context_t &context,
		unsigned int &i, unsigned int &before, std::list<unsigned int> st
) {
	using namespace cuttle;

	if (tokens[i].type != token_type::atom) {
		return false;
	}

	const funcname_to_id_t::const_iterator& it = context.funcname_to_id.find(tokens[i].value);
	if (it == context.funcname_to_id.end()) {
		return false;
	}

	function_id_t func_id = it->second;
	const function_t& func = context.funcs[func_id];
	tree.src[i].resize(func.args_number);

	if (func.type == function_type::postfix || func.type == function_type::infix) {
		unsigned int argi = st.front();
		unsigned int argi_prev = *(++st.cbegin());
		while (argi != CALL_TREE_SRC_UNDEFINED && !tree.src[argi].empty()) {
			function_id_t check_func_id;
			if (argi == tokens.size()) {
				check_func_id = FUNCTION_ID_UNKNOWN;
			} else {
				check_func_id = context.funcname_to_id[tokens[argi].value];
			}
			if ((context.funcs[check_func_id].type == function_type::postfix &&
				 context.funcs_prior.priors[check_func_id].prior == context.funcs_prior.priors[func_id].prior)
				|| context.funcs_prior.priors[check_func_id].prior > context.funcs_prior.priors[func_id].prior) {
				break;
			}
			if (context.funcs[check_func_id].type == function_type::postfix) {
                argi = CALL_TREE_SRC_UNDEFINED;
//                break;
				throw parse_error("'" + tokens[i].value + "' is a postfix or infix function and receives " +
								  std::to_string(func.args_number) + " arguments");
			}
			argi_prev = argi;

			auto j = tree.src[argi].size();
			while (j >= 0 && tree.src[argi][j] == CALL_TREE_SRC_UNDEFINED) --j;
			if (j < 1) {
//                argi = CALL_TREE_SRC_UNDEFINED;
//                break;
				throw parse_error("'" + tokens[i].value + "' is a postfix or infix function and receives " +
								  std::to_string(func.args_number) + " arguments");
			}
            argi = tree.src[argi][j - 1];
		}
		if (argi == CALL_TREE_SRC_UNDEFINED) {
		    tree.src[i][0] = CALL_TREE_SRC_UNDEFINED;
        } else {
            tree.src[i][0] = argi;
            if (argi_prev != CALL_TREE_SRC_UNDEFINED) {
				auto j = tree.src[argi_prev].size();
				while (j >= 0 && tree.src[argi_prev][j] == CALL_TREE_SRC_UNDEFINED) --j;
				if (j < 1) {
					throw parse_error("'" + tokens[i].value + "' is a postfix or infix function and receives " +
									  std::to_string(func.args_number) + " arguments");
                } else {
                    tree.src[argi_prev][j - 1] = i;
                }
				--before;
			} else {
                tree.src[i][0] = CALL_TREE_SRC_UNDEFINED;
            }
		}
	}

	if (func.type == function_type::postprefix) {
        unsigned int j = i + 1;
        unsigned int argn = 0;
        for (; ; ++argn, ++j) {
            if (j >= tokens.size()) {
                throw parse_error("'" + tokens[i].value + "' is a postprefix function and must be enclosed with '" + context.end_function_name[func_id] + "'");
            }
            tree.src[i].resize(argn + 1);
            tree.src[i][argn] = CALL_TREE_SRC_UNDEFINED;
            unsigned int saved_j = j;
            st.push_front(i);
            parse_function_call(tokens, tree, context, j, argn, st);
            if (tree.src[i][argn] == CALL_TREE_SRC_UNDEFINED) {
                tree.src[i][argn] = saved_j;
            }
            if (tokens[saved_j].type == token_type::atom && tokens[saved_j].value == context.end_function_name[func_id]) {
                break;
            }
        }
        i = j;
    } else if (func.type == function_type::prefix || func.type == function_type::infix) {
		unsigned int j = i + 1;
		unsigned int argn = 0;
		if (func.type == function_type::infix) {
			argn = 1;
		}
		for (; argn < func.args_number; ++argn, ++j) {
			if (j >= tokens.size()) {
			    throw parse_error("'" + tokens[i].value + "' receives " + std::to_string(func.args_number) + " arguments");
			}
			tree.src[i][argn] = CALL_TREE_SRC_UNDEFINED;
			unsigned int saved_j = j;
			st.push_front(i);
			parse_function_call(tokens, tree, context, j, argn, st);
			if (tree.src[i][argn] == CALL_TREE_SRC_UNDEFINED) {
				tree.src[i][argn] = saved_j;
			}
		}
		i = j - 1;
	}

	return true;
}

void cuttle::parse(const tokens_t& tokens, call_tree_t& tree, context_t& context) {
	using namespace cuttle;

	unsigned int i = 0;
	tree.src.resize(tokens.size() + 1);
	auto& args = tree.src.back();
	unsigned int argn = 0;
//	int prev_i = -1;
	for (; i < tokens.size(); ++i, ++argn) {
		unsigned int saved_i = i;
//		if (prev_i != -1) {
//            parse_function_call(tokens, tree, context, i, argn,
//                                {prev_i, (unsigned int) tree.src.size() - 1, CALL_TREE_SRC_UNDEFINED});
//        } else {
            parse_function_call(tokens, tree, context, i, argn,
                                {(unsigned int) tree.src.size() - 1, CALL_TREE_SRC_UNDEFINED});

//        }

		if (args.size() <= argn) {
			args.push_back(saved_i);
		} else {
			if (args[argn] != CALL_TREE_SRC_UNDEFINED) continue;
			args[argn] = saved_i;
		}
//		prev_i = saved_i;
	}
}