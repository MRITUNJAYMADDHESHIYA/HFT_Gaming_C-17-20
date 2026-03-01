//1.static_cast:- is used for compile-time conversions that are checked by the compiler. It is mainly used when you know the conversion is safe.
//2.dynamic_cast:- is used for runtime-checked conversions, primarily in polymorphic class hierarchies. It ensures that the conversion is valid at runtime and returns nullptr (for pointers) or throws an exception (for references) if the conversion fails.


#include <iostream>
using namespace std;

struct Base{ virtual ~Base(){}};
struct Derived : Base {};

int main(){
    Base* b = new Base{};

    //static_cast - no safety check
    Derived* d1 = static_cast<Derived*>(b);
    cout<< "Static_cast done\n";

    //dynamic_cast - runtime safety check
    Derived* d2 = dynamic_cast<Derived*>(b);
    if(d2){
        cout<< "Dynamic_cast succeeded\n";
    } else {
        cout<< "Dynamic_cast failed\n";
    }

    delete b;
}