#pragma once

#include <vector>

namespace cuttle {
	using tree_src_t = std::vector<std::vector<int> >;
    typedef struct call_tree {
        tree_src_t src;
    } call_tree_t;
}