#pragma once

#include <string>
#include <vector>

namespace cuttle {
	enum token_type {
		number,
		string,
		atom,
        macro_if,
        macro_p,
        macro_pf,
        macro_ps,
		unknown
	};

	struct token_t {
		token_type type;
		const std::string value;
		const unsigned short line = 0u;
		const unsigned short col = 0u;
	};

	using tokens_t = std::vector<token_t>;
}
