#pragma once

#include <vector>
#include <limits>

namespace cuttle {
    const unsigned int CALL_TREE_SRC_UNDEFINED = std::numeric_limits<unsigned int>::max();
	using tree_src_t = std::vector<std::vector<unsigned int> >;
	struct call_tree_t {
        tree_src_t src;
    };
}