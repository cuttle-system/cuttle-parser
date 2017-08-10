#include "token.hpp"

bool husky::operator>=(const token_t& l, const token_t& r)
{
    return r.line - l.line == 0 && r.col - l.col == 1;
}