#pragma once

#include "token.hpp"
#include <string>
#include <vector>

namespace husky {
    void tokenize(
        const std::string& query,
        std::vector<token_t *>& tokens,
        unsigned short line = 1
    );
}
