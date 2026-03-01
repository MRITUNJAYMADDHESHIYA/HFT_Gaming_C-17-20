#include <iostream>

void printValue(const int& x) {
    // x is a constant reference, cannot modify the value of x
    // but can read its value
    std::cout << "Value: " << x << std::endl;
    // x = 10; // Error: Cannot modify a const parameter
}

int main() {
    int num = 5;
    const int constNum = 10;

    printValue(num); // passing a non-const object
    printValue(constNum); // passing a const object

    return 0;
}
