//References allow you to work directly with the original object without making a copy. 
//This can be more efficient in terms of memory usage and execution speed, especially for large objects.


#include <iostream>
#include <chrono>

using namespace std;

void function1(int &y) {
    // Some computation
    for (int i = 0; i < 1000000; ++i) {
        // Some computation
    }
}

void function2(int y) {
    // Some computation
    for (int i = 0; i < 1000000; ++i) {
        // Some computation
    }
}

int main() {
    int x = 7;

    // Measure time for function1
    auto start1 = chrono::high_resolution_clock::now();
    function1(x);
    auto end1 = chrono::high_resolution_clock::now();
    cout << "Function 1 execution time: " << chrono::duration<double>(end1 - start1).count() << " seconds" << endl;

    // Measure time for function2
    auto start2 = chrono::high_resolution_clock::now();
    function2(x);
    auto end2 = chrono::high_resolution_clock::now();
    cout << "Function 2 execution time: " << chrono::duration<double>(end2 - start2).count() << " seconds" << endl;

    return 0;
}
