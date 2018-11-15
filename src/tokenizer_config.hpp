#pragma once

#include <map>
#include <set>

namespace cuttle {
	using tokenizer_symbol_set_t = std::set<std::string>;
    using tokenizer_range_map_t = std::map<std::string, tokenizer_symbol_set_t>;
    using tokenizer_map_t = std::map<std::string, std::string>;

	enum class tokenizer_range_type {
		formatted_string,
		normal_string,
		separated_symbols,
		comments,
        macro_if,
        macro_elif,
        macro_else,
        macro_eq,
        macro_block_start,
        macro_block_end,
        macro_state,
        macro_ps,
        macro_pf,
        macro_p
	};

	struct tokenizer_config_t {
		tokenizer_range_map_t formatted_string;
		tokenizer_range_map_t normal_string;
		tokenizer_symbol_set_t separated_symbols;
		tokenizer_range_map_t comments;

        tokenizer_map_t formatted_characters;
        tokenizer_map_t formatted_characters_output;

		tokenizer_symbol_set_t macro_if;
		tokenizer_symbol_set_t macro_elif;
		tokenizer_symbol_set_t macro_else;
		tokenizer_symbol_set_t macro_eq;
        tokenizer_symbol_set_t macro_block_start;
        tokenizer_symbol_set_t macro_block_end;
        tokenizer_range_map_t macro_state;
        tokenizer_range_map_t macro_ps;
		tokenizer_range_map_t macro_pf;
		tokenizer_range_map_t macro_p;

        bool separate_digit_and_alpha;
	};
}
