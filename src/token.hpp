#pragma once

#include <string>
#include <vector>

namespace cuttle {
	enum class token_type {
		number,
		string,
		atom,
		unknown
	};

	using token_t = struct token {
		token_type type;
		const std::string value;
		const unsigned short line;
		const unsigned short col;
	};

	using tokens_t = std::vector<token_t>;
}
