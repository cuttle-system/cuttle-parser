#pragma once

#include "token.hpp"
#include <vector>
#include <memory>

namespace husky {
    class Tokenizer {
    public:
        static void Tokenize(
            const std::string& query,
            std::vector<std::unique_ptr<Token>>& tokens);
    };
}
