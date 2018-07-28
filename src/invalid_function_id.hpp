#pragma once

#include <stdexcept>

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define validate_function_id(id) validate_function_id_(id, __FILE__ ":" STRINGIZE(__LINE__))
#define validate_after_function_id(id) validate_after_function_id_(id, __FILE__ ":" STRINGIZE(__LINE__))

namespace cuttle {
    class invalid_function_id : public std::invalid_argument {
    public:
        explicit invalid_function_id(function_id_t id, const std::string& place)
                : invalid_argument("Invalid function id: " + std::to_string(id) + " " + place) {}
    };

    inline void validate_function_id_(function_id_t id, const char *place) {
        if (id < FUNCTION_ID_START) {
            throw invalid_function_id(id, place);
        }
    }

    inline void validate_after_function_id_(function_id_t id, const char *place) {
        if (id < FUNCTION_ID_UNKNOWN || id == FUNCTION_ID_LAST) {
            throw invalid_function_id(id, place);
        }
    }
}