#include <ostream>
#include "token_methods.hpp"

bool operator>=(const cuttle::token_t &l, const cuttle::token_t &r) {
    return r.line - l.line == 0 && r.col - l.col == 1;
}

cuttle::token_type cuttle::token_type_from_string(const std::string &str) {
    if (str == "number") {
        return token_type::number;
    } else if (str == "string") {
        return token_type::string;
    } else if (str == "atom") {
        return token_type::atom;
    } else if (str == "macro_if") {
        return token_type::macro_if;
    } else if (str == "macro_p") {
        return token_type::macro_p;
    } else if (str == "macro_pf") {
        return token_type::macro_pf ;
    } else if (str == "macro_ps") {
        return token_type::macro_ps;
    } else if (str == "macro_elif") {
        return token_type::macro_elif;
    } else if (str == "macro_else") {
        return token_type::macro_else;
    } else if (str == "macro_eq") {
        return token_type::macro_eq;
    } else if (str == "macro_block_start") {
        return token_type::macro_block_start;
    } else if (str == "macro_block_end") {
        return token_type::macro_block_end;
    } else if (str == "macro_set") {
        return token_type::macro_set;
    } else if (str == "macro_get") {
        return token_type::macro_get;
    } else {
        return token_type::unknown;
    }
}

const char *cuttle::token_type_to_string(cuttle::token_type const &type) {
    switch (type) {
        case token_type::number:
            return "number";
        case token_type::string:
            return "string";
        case token_type::atom:
            return "atom";
        case token_type::macro_if:
            return "macro_if";
        case token_type::macro_p:
            return "macro_p";
        case token_type::macro_pf:
            return "macro_pf";
        case token_type::macro_ps:
            return "macro_ps";
        case token_type::macro_elif:
            return "macro_elif";
        case token_type::macro_else:
            return "macro_else";
        case token_type::macro_eq:
            return "macro_eq";
        case token_type::macro_block_start:
            return "macro_block_start";
        case token_type::macro_block_end:
            return "macro_block_end";
        case token_type::macro_set:
            return "macro_set";
        case token_type::macro_get:
            return "macro_get";
        default:
            return "unknown";
    }
}

std::ostream &operator<<(std::ostream &stream, cuttle::token_type const &type) {
    using namespace cuttle;
    stream << token_type_to_string(type);
    return stream;
}
