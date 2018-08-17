#pragma once

#include <map>
#include <set>

namespace cuttle {
	using tokenizer_symbol_set_t = std::set<std::string>;
	using tokenizer_range_map_t = std::map<std::string, tokenizer_symbol_set_t>;

	enum class tokenizer_range_type {
		formatted_string,
		normal_string,
		separated_symbols,
		comments
	};

	struct tokenizer_config_t {
		tokenizer_range_map_t formatted_string;
		tokenizer_range_map_t normal_string;
		tokenizer_symbol_set_t separated_symbols;
		tokenizer_range_map_t comments;

		bool separate_digit_and_alpha;
	};
}
