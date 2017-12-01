#include <string>
#include <vector>
#include <ctype.h>
#include "token.hpp"
#include "tokenizer.hpp"
#include "parse_error.hpp"
#include "formatted_character.hpp"

using namespace cuttle;

#define found_range_start(name) { \
	range_found = true; \
	range_type = tokenizer_range_type::##name; \
}

#define register_range_type(name, func) \
	if (!range_found) { \
		tokenizer_range_map_t container = config.##name; \
		if (find_symbol(container, range_end, symbol)) { \
			func(); \
			found_range_start(name); \
		} \
	}

#define register_set_type(name, func) \
	if (!range_found) { \
		tokenizer_symbol_set_t container = config.##name; \
		if (find_symbol(container, symbol)) { \
			func(); \
		} \
	}

class Tokenizer {
public:
	token_type type = token_type::unknown;
	bool range_found = false;
	bool advance = false;
	tokenizer_range_type range_type = tokenizer_range_type();
	tokenizer_symbol_set_t range_end;
	unsigned short i_start = 0, line_start, i_line_start = 0;
	std::string acc = "";
	std::string str;
	tokenizer_config_t config;
	unsigned int i;
	unsigned short line;
	
	const int symbol_check_length = 3;

	std::string symbol;

	Tokenizer(const tokenizer_config_t& config,
		const std::string &query,
		tokens_t& tokens,
		unsigned short line_
	) {
		str = query + '\n';
		line_start = line_;
		this->config = config;
		this->line = line_;

		for (i = 0; i < str.length(); ++i) {
			if (str[i] == '\n') {
				i_line_start = i + 1;
				++line;
			}

			advance = true;

			register_range_type(formatted_string, [&] () {
				reset_acc(tokens);
				i_start -= symbol.length();
				type = token_type::string;
				advance = false;
			});
			register_range_type(normal_string, [&] () {
				reset_acc(tokens);
				i_start -= symbol.length();
				type = token_type::string;
				advance = false;
			});
			register_range_type(comments, [&] () {
				reset_acc(tokens);
				i_start -= symbol.length();
				advance = false;
			});
			register_set_type(separated_symbols, [&] () {
				reset_acc(tokens);
				type = token_type::atom;
				acc = symbol;
				i_start -= symbol.length();
				reset_acc(tokens);
				advance = false;
			});

			if (!advance) {

			} else if (range_found) {
				if (range_type == tokenizer_range_type::formatted_string && str[i] == '\\') {
					if (str[i] == '\\') {
						if (i + 1 >= str.length()) {
							throw parse_error("trailing '\\'");
						} else {
							acc += formatted_character(str[i], str[i + 1]);
							++i;
						}
					}
				}
				else if (find_symbol(range_end, symbol)) {
					reset_acc(tokens);
				} else if (range_type == tokenizer_range_type::comments) {
					//
				} else {
					acc += str[i];
				}
				continue;
			} else if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
				|| (type == token_type::number && !isdigit(str[i]))
				|| (type == token_type::atom && isdigit(str[i]) && config.separate_digit_and_alpha)
			) {
				if (acc != "" && !(str[i] == ' ' || str[i] == '\n' || str[i] == '\t')) --i;
				reset_acc(tokens);
			} else {
				if (acc == "") {
					type = isdigit(str[i]) ? token_type::number : token_type::atom;
				}
				acc += str[i];
			}
		}
	}

	void reset_acc(tokens_t& tokens) {
		range_found = false;
		if (acc != "") {
			tokens.push_back(token_t{
				(token_type)type, acc, line_start, ++i_start
			});
			acc = "";
		}
		i_start = i - i_line_start + 1;
		line_start = line;
		type = token_type::unknown;
	}

	/*
	 * NOTE: current symbols can only be <= 3
	 */
	bool find_symbol(tokenizer_range_map_t container, tokenizer_symbol_set_t& range, std::string& symbol) {
		std::string val = "";
		auto it = container.end();
		for (int j = i; j - i < symbol_check_length && j < str.length(); ++j) {
			val += str[j];
			it = container.find(val);
			if (it != container.end()) {
				range = it->second;
				symbol = val;
				i = j;
				return true;
			}
		}
		return false;
	}

	/*
	* NOTE: current symbols can only be <= 3
	*/
	bool find_symbol(tokenizer_symbol_set_t container, std::string& symbol) {
		std::string val = "";
		auto it = container.end();
		for (int j = i; j - i < symbol_check_length && j < str.length(); ++j) {
			val += str[j];
			it = container.find(val);
			if (it != container.end()) {
				symbol = *it;
				i = j;
				return true;
			}
		}
		return false;
	}
};

void cuttle::tokenize(
	const tokenizer_config_t& config,
    const std::string &query,
    tokens_t& tokens,
    unsigned short line
) {
	std::string normalized_query = query;
	if (normalized_query.back() != '\n') {
		normalized_query.push_back('\n');
	}
	(void) Tokenizer(config, normalized_query, tokens, line);
}