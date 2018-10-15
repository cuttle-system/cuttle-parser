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
    } else {
        return token_type::unknown;
    }
}

std::ostream &operator<<(std::ostream &stream, cuttle::token_type const &type) {
    using namespace cuttle;
    switch (type) {
        case token_type::number:
            stream << "number";
            break;
        case token_type::string:
            stream << "string";
            break;
        case token_type::atom:
            stream << "atom";
            break;
        case token_type::macro_if:
            stream << "macro_if";
            break;
        case token_type::macro_p:
            stream << "macro_p";
            break;
        case token_type::macro_pf:
            stream << "macro_pf";
            break;
        case token_type::macro_ps:
            stream << "macro_ps";
            break;
        case token_type::unknown:
            stream << "unknown";
    }
    return stream;
}
