#pragma once

#include <vector>

namespace cuttle {
	using tree_src_t = std::vector<std::vector<unsigned int> >;
	struct call_tree_t {
        tree_src_t src;
    };
}