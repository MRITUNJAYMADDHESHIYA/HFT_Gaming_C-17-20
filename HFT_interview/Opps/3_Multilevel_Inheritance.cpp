#include<iostream>
using namespace std;

class A{
    public:
        void fun(){
            cout<< "A::fun()" << endl;
        }
};

class B : public A{
    public:
        void fun(){
            cout<< "B::fun()" << endl;
        }
};

class C : public B{
    public:
        virtual void fun(){
            cout<< "C::fun()" << endl;
        }
};

class D : public C{
    public:
        void fun() override{
            cout<< "D::fun()" << endl;
        }
};

int main(){
    // B b; //object created
    // b.fun();

    // A a; //object created
    // a.fun();

    // //////Reference
    // A& a1 = b;
    // a1.fun();

    // C c; //object created
    // c.fun();

    ///////////////////////////
    D d; //object created

    A& a = d;
    a.fun();

    B& b = d;
    b.fun();

    C& c = d;
    c.fun();

    d.fun();

    return 0;
}