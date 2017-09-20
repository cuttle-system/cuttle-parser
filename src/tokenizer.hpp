#pragma once

#include "token.hpp"
#include <string>
#include <vector>

namespace cuttle {
    void tokenize(
        const std::string& query,
        tokens_t& tokens,
        unsigned short line = 1
    );
}
