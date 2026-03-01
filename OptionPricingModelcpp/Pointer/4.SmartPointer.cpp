//smart pointers are objects that manage the lifetime of dynamically allocated memory (heap memory) to ensure that it is properly released when no longer needed, preventing memory leaks and dangling pointers.
//1.unique_ptr
//2.shared_ptr
//3.weak_ptr
#include<iostream>
#include<memory>
using namespace std;

class MyClass{
    public:
        MyClass(){
            cout<<"Constructor invoked" <<endl;
        }
        ~MyClass(){
            cout<<"Destructor invoked" <<endl;
        }
};

////1.unique pointer
// int main(){

//     unique_ptr<MyClass>unPtr1 = make_unique<MyClass>();

//     // unique_ptr<int> unPtr1 = make_unique<int>(25);
//     // unique_ptr<int> unPtr2 = move(unPtr1); /Transfer of ownerShip

//     // cout<< "unPtr2 " <<*unPtr2 <<endl;
//     // cout<< "unPtr1 " <<*unPtr1 <<endl;

//     // cout<<unPtr1<<endl; //addres
//     // cout<<*unPtr1<<endl; //value

//     system("pause>nul");
// }

// //2.shared pointer
// int main(){
//     shared_ptr<MyClass> shPtr1 = make_shared<MyClass>();
//     cout<<"shared count: "<< shPtr1.use_count()<<endl; //no. of owner that memory location

//     //automatic memory deallocation using curly braket
//     {shared_ptr<MyClass> shPtr2 = shPtr1;
//     cout<<"shared count: "<<shPtr1.use_count()<<endl;} //now 2 owner
    
//     cout<<"shared count: "<<shPtr1.use_count()<<endl;
// }



//3.Weak pointer
//weak_ptr does not own the object. It holds a non-owning reference to an object managed by shared_ptr.
int main(){
    weak_ptr<int> wePtr1;
    {
        shared_ptr<int> shPtr1 = make_shared<int>(24);
        wePtr1 = shPtr1; //same memory location assign
    }
}


