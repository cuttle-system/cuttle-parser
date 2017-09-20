#pragma once

#include <vector>

namespace husky {
	using tree_src_type = std::vector<std::vector<int> >;
    typedef struct call_tree {
        tree_src_type src;
    } call_tree_t;
}