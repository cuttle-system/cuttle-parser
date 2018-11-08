#pragma once

#include <vector>
#include <limits>
#include <set>

namespace cuttle {
	using tree_src_element_t = unsigned int;
    using tree_src_elements_t = std::vector<tree_src_element_t>;
    using tree_src_t = std::vector<tree_src_elements_t>;

    const tree_src_element_t CALL_TREE_SRC_NIL = std::numeric_limits<tree_src_element_t>::max() - 1;
    const tree_src_element_t CALL_TREE_SRC_UNDEFINED = std::numeric_limits<tree_src_element_t>::max();

    struct call_tree_t {
        tree_src_t src;
        std::set<tree_src_element_t> finished_funcs;
    };
}