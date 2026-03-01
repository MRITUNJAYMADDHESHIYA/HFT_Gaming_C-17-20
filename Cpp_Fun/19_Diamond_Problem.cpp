#include<iostream>
using namespace std;

class A{
    public:
        void show(){
            cout<< " class A\n";
        }
};

class B: public A {};
class C: public A {};
class D: public B, public C {};

int main(){
    D obj;
    //obj.show(); //error: request for member 'show' is ambiguous
    obj.B::show();
    obj.C::show();

    return 0;
}


///solution
class B: virtual A {};
class C: virtual A {};
class D: public B, public C {};

int main(){
    D obj;
    obj.show(); // now no ambiguity

    return 0;
}