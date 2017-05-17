#pragma once

#include "token.hpp"
#include <list>
#include <memory>

namespace husky {
    class Tokenizer {
    public:
        static void Tokenize(
            const std::string& query, std::list<std::unique_ptr<Token>>& tokens);
    };
}
