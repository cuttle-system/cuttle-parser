#pragma once

#include "token.hpp"

bool operator>=(const cuttle::token_t& l, const cuttle::token_t& r);
std::ostream &operator<<(std::ostream &stream, cuttle::token_type const& type);
