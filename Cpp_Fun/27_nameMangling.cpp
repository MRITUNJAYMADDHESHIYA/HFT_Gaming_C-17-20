//So, the compiler “mangles” (i.e., changes) the function names into unique encoded names that include extra information such as:
// Function name
// Parameter types
// Namespace/class
// Calling convention


//C++ supports function overloading, namespaces, and classes, which all allow multiple functions to have the same name but different signatures.
#include<iostream>
using namespace std;

void show(int a){
    cout<<"Integer version: "<< a << endl;
}

void show(double b){
    cout<<"Double version: "<< b << endl;
}

void show(string c){
    cout<<"String version: "<< c << endl;
}

int main(){
    show(42);          // Calls the integer version
    show(3.14);       // Calls the double version
    show("Hello");    // Calls the string version

    return 0;
}