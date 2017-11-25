#pragma once

#include <string>

namespace cuttle {
    enum function_type {
        PREFIX_FUNCTION,
        INFIX_FUNCTION,
        POSTFIX_FUNCTION
    };

    typedef struct function {
        enum function_type type;
        int args_number = 0;
    } function_t;
}
