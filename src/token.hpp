#pragma once

#include <string>

namespace husky {
    enum token_type {
        NUMBER_TOKEN,
        STRING_TOKEN,
        ATOM_TOKEN
    };

    typedef struct token {
        enum token_type type;
        const std::string value;
        const unsigned short line;
        const unsigned short col;
    } token_t;

    bool operator>=(const token_t& l, const token_t& r);
}
