#include <iostream>
using namespace std;

struct Demo {
    string name;
    Demo(string n) : name(n) { cout << "Construct " << name << endl; }
    ~Demo() { cout << "Destruct " << name << endl; }
};

void C() {
    Demo d3("C");
    throw runtime_error("Error!");
}

void B() {
    Demo d2("B");
    C();
}

void A() {
    Demo d1("A");
    B();
}

int main() {
    try{
        A();
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
}
