#pragma once

#include <vector>
#include <limits>

namespace cuttle {
	using tree_src_element_t = unsigned int;
    using tree_src_elements_t = std::vector<tree_src_element_t>;
    using tree_src_t = std::vector<tree_src_elements_t>;

    const tree_src_element_t CALL_TREE_SRC_UNDEFINED = std::numeric_limits<tree_src_element_t>::max();

    struct call_tree_t {
        tree_src_t src;
    };
}