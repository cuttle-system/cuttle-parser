#include <ostream>
#include "token_methods.hpp"

bool operator>=(const cuttle::token_t &l, const cuttle::token_t &r)
{
    return r.line - l.line == 0 && r.col - l.col == 1;
}

std::ostream &operator<<(std::ostream &stream, cuttle::token_type const &type)
{
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
    case token_type::unknown:
        stream << "unknown";
    }
    return stream;
}
