//inline variables were introduced in C++17 to allow defining global or static variables in header files without causing multiple definition linker errors.

//inline tells the compiler:
//"It’s okay if this variable is defined in multiple places, just merge them into one."

#include <iostream>
#include "file1.hpp"
#include "file2.hpp"
using namespace std;

int main() {
    A a;
    a.print();
    return 0;
}