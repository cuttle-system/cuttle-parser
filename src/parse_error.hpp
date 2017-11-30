#pragma once

#include <stdexcept>

namespace cuttle {
	class parse_error : public std::runtime_error
	{
	public:
		parse_error() : runtime_error("Unknown parse error") {}
		parse_error(std::string msg) : runtime_error(msg.c_str()) {}
	};
}