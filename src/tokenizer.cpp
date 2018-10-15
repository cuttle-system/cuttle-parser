#include <string>
#include <vector>
#include "token.hpp"
#include "tokenizer.hpp"
#include "parse_error.hpp"
#include "formatted_character.hpp"

using namespace cuttle;

#define found_range_start(name) { \
	range_found = true; \
	range_type = tokenizer_range_type::name; \
}

#define register_range_type(name, func) \
	if (!range_found) { \
		tokenizer_range_map_t container = config.name; \
		if (find_symbol(container, symbol, range_end)) {    \
			func(); \
			found_range_start(name); \
		} \
	}

#define register_set_type(name, func) \
	if (!range_found) { \
		tokenizer_symbol_set_t container = config.name; \
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
	unsigned short i_start = 0, line_start;
	unsigned int i_line_start = 0;
	std::string acc = "";
	std::string str;
	tokenizer_config_t config;
	unsigned int i;
	unsigned short line;
	
	const unsigned int symbol_check_length = 10;

	std::string symbol;

	Tokenizer(const tokenizer_config_t& config,
		const std::string &query,
		tokens_t& tokens,
		unsigned short line_
	) {
		str = query + "\n";
		line_start = line_;
		this->config = config;
		this->line = line_;

		for (i = 0; i < str.length(); ++i) {
			if (str[i] == '\n') {
				i_line_start = i + 1;
				++line;
			}

			advance = true;

			register_set_type(macro_if, [&] () {
                reset_acc(tokens);
                type = token_type::macro_if;
                acc = symbol;
                i_start -= symbol.length();
                reset_acc(tokens);
                advance = false;
			});
            register_range_type(macro_ps, [&] () {
                reset_acc(tokens);
                i_start -= symbol.length();
                type = token_type::macro_ps;
                advance = false;
            });
            register_range_type(macro_pf, [&] () {
                reset_acc(tokens);
                i_start -= symbol.length();
                type = token_type::macro_pf;
                advance = false;
            });
			register_range_type(macro_p, [&] () {
				reset_acc(tokens);
				i_start -= symbol.length();
				type = token_type::macro_p;
				advance = false;
			});
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
                //
			} else if (range_found) {
                bool formatted_character_found = false;

                if (range_type == tokenizer_range_type::formatted_string) {
                    if (!config.formatted_characters.empty()) {
                        if (find_symbol(config.formatted_characters, symbol)) {
                            acc += symbol;
                            formatted_character_found = true;
                        }
                    } else {
                        if (str[i] == '\\') {
                            if (i + 1 >= str.length()) {
                                throw parse_error("trailing '\\'");
                            } else {
                                acc += formatted_character(str[i], str[i + 1]);
                                ++i;
                                formatted_character_found = true;
                            }
                        }
                    }
                }

                if (formatted_character_found) {
                    //
			    } else if (find_symbol(range_end, symbol)) {
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
				if (!acc.empty() && !(str[i] == ' ' || str[i] == '\n' || str[i] == '\t')) --i;
				reset_acc(tokens);
			} else {
				if (acc.empty()) {
					type = isdigit(str[i]) ? token_type::number : token_type::atom;
				}
				acc += str[i];
			}
		}
	}

	void reset_acc(tokens_t& tokens) {
		range_found = false;
		if (type != token_type::unknown) {
			tokens.push_back(token_t{
				type, acc, line_start, ++i_start
			});
			acc = "";
		}
		i_start = (unsigned short) (i - i_line_start + 1);
		line_start = line;
		type = token_type::unknown;
	}

	/*
	 * NOTE: current symbols can only be <= 3
	 */
	bool find_symbol(tokenizer_range_map_t container, std::string& symbol, tokenizer_symbol_set_t& range) {
        tokenizer_range_map_t::iterator it;
		std::string val;
        unsigned int j = i;
        construct_symbol_val(val, j);
		for (; j >= i; --j) {
			it = container.find(val);
			if (it != container.end()) {
                symbol = val;
                range = it->second;
                i = j;
				return true;
			}
            if (j == 0) break;
            val.pop_back();
		}
		return false;
	}

	/*
	 * NOTE: current symbols can only be <= 3
	 */
	bool find_symbol(tokenizer_symbol_set_t container, std::string& symbol) {
        tokenizer_symbol_set_t::iterator it;
		std::string val;
        unsigned int j = i;
        construct_symbol_val(val, j);
		for (; j >= i; --j) {
			it = container.find(val);
			if (it != container.end()) {
                symbol = val;
                i = j;
				return true;
			}
            if (j == 0) break;
            val.pop_back();
		}
		return false;
	}

	/*
	 * NOTE: current symbols can only be <= 3
	 */
	bool find_symbol(tokenizer_map_t container, std::string& symbol) {
		tokenizer_map_t::iterator it;
		std::string val;
		unsigned int j = i;
		construct_symbol_val(val, j);
		for (; j >= i; --j) {
			it = container.find(val);
			if (it != container.end()) {
				symbol = it->second;
				i = j;
				return true;
			}
			if (j == 0) break;
			val.pop_back();
		}
		return false;
	}

    void construct_symbol_val(std::string &val, unsigned int &j) {
		while (j - i < symbol_check_length && j < str.length()) {
			val += str[j];
            ++j;
        }
        if (j == 0) {
            (void) j;
        }
        --j;
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
