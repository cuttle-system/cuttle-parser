#pragma once

#include <string>

#define FUNCTION_ID_UNKNOWN -1

namespace cuttle {
	using function_id_t = int;
    enum function_type {
        PREFIX_FUNCTION,
        INFIX_FUNCTION,
        POSTFIX_FUNCTION
    };

    typedef struct function {
		function_id_t id;
        enum function_type type;
        int args_number = 0;
    } function_t;
}
