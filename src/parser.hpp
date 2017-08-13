#pragma once

#include <vector>
#include "call_tree.hpp"
#include "context.hpp"
#include "token.hpp"

namespace husky {
    void parse(const std::vector<token_t *>& tokens, call_tree_t& tree, context_t& context);
}