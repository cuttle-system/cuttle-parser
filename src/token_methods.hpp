#pragma once

#include "token.hpp"

bool operator>=(const cuttle::token_t& l, const cuttle::token_t& r);
std::ostream &operator<<(std::ostream &stream, cuttle::token_type const& type);

namespace cuttle {
    cuttle::token_type token_type_from_string(const std::string &str);
    const char *token_type_to_string(token_type const &type);
}