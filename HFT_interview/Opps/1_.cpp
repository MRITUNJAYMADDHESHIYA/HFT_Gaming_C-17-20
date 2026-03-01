//1.friend--->allows class B to access: all private and protected members of class A.
//2.friendship is not mutual and not inherited.

#include<iostream>
using namespace std;

class B;
class A{
    private:
        friend class B;

        int _num{};
};

class B{
    public:
        void fun(){
            A a;
            cout<< a._num << endl;
            a._num = 10;
            cout<< a._num << endl;
        }
};

//it's give compilation failed
class C : public B{
    public:
        void func(){
            A a;
            cout<< a._num << endl;
            a._num = 10;
            cout<< a._num << endl;
        }
};

int main(){
    B b;
    b.fun();

    return 0;
}