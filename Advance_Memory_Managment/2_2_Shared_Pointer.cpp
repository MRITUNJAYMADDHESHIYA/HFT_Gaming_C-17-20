////std::shared_ptr:-(It allows multiple pointers to share ownership of a dynamically allocated object. The object is deleted when the last shared_ptr pointing to it is destroyed.)
//Shared ptr is thread safe and not thread safe ptr1; 
// a.control block is thread safe
// b.managed object is not thread safe


// std::shared_ptr<int> ptr2 = std::make_shared<int>(20);
// std::shared_ptr<int> ptr3 = ptr2; // ptr2 and ptr3 share ownership of the same object

//issue:-
//A major issue with std::shared ptr arises in cases where cyclic references are created.(fixed by std::weak_ptr)


#include<iostream>
#include <memory>
using namespace std;

class temp{
        int x;
    public:
        temp(int x): x{x} {}
        int getX() {return x;}

    ~temp(){cout<< "Temp Destructor"<<endl;}
};

int main(){
    temp *ptr = new temp(10); // Dynamically allocated object
    cout << ptr->getX() << endl; // Accessing the object
    delete ptr; // Manually deallocating memory

    //2
    std::shared_ptr<temp> ptr1(new temp(20)); // Using shared_ptr for automatic memory management
    cout << ptr1->getX() << endl; // Accessing the object managed by
    cout<< ptr1.use_count() << endl; // Displaying the reference count
    std::shared_ptr<temp> ptr2 = ptr1; // ptr1 and ptr2 share ownership of the same object
    cout<<ptr2.use_count() << endl; // Reference count increases
    return 0;
}


