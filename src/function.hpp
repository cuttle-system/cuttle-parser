#pragma once

#include <string>

namespace cuttle {
    enum class function_type {
        prefix,
        infix,
        postfix
    };

    using function_t = struct function {
        function_type type = function_type::prefix;
        unsigned int args_number = 0;
    };
}
