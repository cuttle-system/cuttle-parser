#pragma once

#include <string>
#include <vector>
#include "token.hpp"
#include "tokenizer_config.hpp"

namespace cuttle {
    void tokenize(
		const tokenizer_config_t& config,
        const std::string& query,
        tokens_t& tokens,
        unsigned short line = 1
    );
}
