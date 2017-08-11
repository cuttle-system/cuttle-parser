#pragma once

#include <vector>

namespace husky {
    typedef struct call_tree {
        std::vector<std::vector<int> > src;
    } call_tree_t;
}