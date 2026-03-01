//1.[[maybe_unused]]-->This variable/function/parameter may be unused intentionally — don’t warn me.


#include<iostream>
#include<exception>
using namespace std;

//throw an exception on constructor is valid but, not in destructor 
class A{
    public:
        A(){
            // cout<<"A::A() called" <<endl;
            // throw std::runtime_error{"Runtime error in constructor A::A()"};
        }
        ~A(){
            cout<< "Destructor A"<< endl;
            throw std::runtime_error{"Runtime error in destructor A::~A()"};
        }
};

int main(){
    try{
        [[maybe_unused]] A a;
    } catch (std::exception& e){
        cout<< e.what() << endl;
    }
    return 0;
}