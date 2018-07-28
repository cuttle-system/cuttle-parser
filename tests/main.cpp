#include <iostream>
#include "test_manager.hpp"

using namespace std;

int main()
{
	try {
		run_tests();
		cout << "ok" << endl;
	}
	catch (const std::logic_error& e) {
		cout << "logic_error: " << e.what() << endl;
	}
//	getchar();
}
