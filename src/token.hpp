#pragma once

#include <string>
#include <vector>

namespace cuttle {
	enum token_type {
		number,
		string,
		atom,
        macro_if,
        macro_elif,
        macro_else,
        macro_eq,
        macro_block_start,
        macro_block_end,
		macro_set,
		macro_get,
        macro_p,
        macro_pf,
        macro_ps,
		unknown
	};

	struct token_t {
		token_type type;
		std::string value;
		unsigned short line = 0u;
		unsigned short col = 0u;
	};

	using tokens_t = std::vector<token_t>;
}
