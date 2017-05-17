#include <exception>
#include <iostream>
#include "../src/function.hpp"

#include "test_manager.hpp"

using namespace std;

int main(void)
{
    TestManager::RunTests();
    cout << "ok" << endl;
}
