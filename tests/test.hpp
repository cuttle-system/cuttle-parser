#pragma once

#include <string>
#include "call_tree.hpp"

#define TESTCASE std::cout << __func__ << std::endl;

#define AssertTrue(statement, message)                  \
    husky::_AssertTrue((statement), message, __FILE__, __LINE__)

#define AssertEqual(out, exp, message)					\
	husky::_AssertTrue((out) == (exp), message,  __FILE__, __LINE__)

namespace husky {
    void _AssertTrue(
        bool statement, const std::string& message, const char* file, int line
    );

	template <typename T>
	void _AssertEqual(
		T out, T exp,
		const std::string& message, const char* file, int line
	) {
		
	}

    void Log(const std::string &message);
}
