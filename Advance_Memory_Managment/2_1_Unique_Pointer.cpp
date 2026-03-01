////std::unique_ptr:-(It represents exclusive ownership of a dynamically allocated object. When the unique_ptr goes out of scope, it automatically deletes the object it owns.)

//Implement your own unique_ptr
//Garbage-collected---->python, java, go, ....
//not garbage-collected-->C, C++, rust, assembly




// //1.No Copying:-
// std::unique_ptr<int> ptr2 = std::make_unique<int>(20); // Unique ownership
// std::unique_ptr<int> ptr3 = ptr2; // Error: unique_ptr cannot be copied

// //2.Move Semantics:-
// std::unique_ptr<int> ptr4 = std::move(ptr2); // Transfer ownership from ptr2 to ptr4


// //3.Advanced Custom Deleters with std::unique ptr:-Eg:-(lamda function)
// auto customDeleter = [](int* ptr) {
//     std::cout << "Custom deleter called for pointer: " << ptr <<std::endl;
//     delete ptr; // Standard deletion
// };
// // Using a custom deleter with std::unique_ptr
// std::unique_ptr<int, decltype(customDeleter)> ptr(new int(42), customDeleter);



// //eg:- file handling with std::unique_ptr
// struct FileDeleter {
//     void operator()(FILE* file) const {
//         std::cout << "Closing file." << std::endl;
//         fclose(file);
//     }
// };
// //using uniwue_ptr
// std::unique_ptr<FILE, FileDeleter> filePtr(fopen("example.txt", "r"));



//////////////////////////////////////***********************////////////////////////////////////////
#include <iostream>
#include <memory>
using namespace std;

class temp{
        int x;
    public:
        explicit temp(int x): x{x} {}
        int getX() {return x;}

    ~temp(){cout<< "Temp Destructor"<<endl;}
};

int main(){
    //1
    temp *ptr = new temp(10); // Dynamically allocated object
    cout<< ptr->getX() << endl; // Accessing the object
    delete ptr; // Manually deallocating memory

    //2
    std::unique_ptr<temp> ptr1(new temp(20)); // Using unique_ptr for automatic memory management
    cout << ptr1->getX() << endl; // Accessing the object managed by

    //3
    std::unique_ptr<temp> ptr2 = std::make_unique<temp>(30); // Using make_unique for better memory management
    cout << ptr2->getX() << endl; // Accessing the object managed by

    //4
    std::unique_ptr<temp> p1(new temp(40)); // Using unique_ptr with a custom deleter
    std::unique_ptr<temp> p2 = std::make_unique<temp>(50);
    cout<<p1->getX() <<" "<< (*p2).getX() << endl;// Accessing the object managed by p1

    //5
    //we can't copy unique_ptr, but we can transfer ownership using std::move
    std::unique_ptr<temp> p3 = std::move(p1); // Transferring ownership from p1 to p3
    temp* p = p3.get(); // Getting the raw pointer from unique_ptr
    temp* p4 = p2.release(); // Releasing ownership of the object managed by p2
    cout << p->getX() << " " << p4->getX() << endl; // Accessing the objects managed by p3 and p4

    //6
    p2.reset(new temp(60)); // Resetting unique_ptr to a new object
    cout << p2->getX() << endl; // Accessing the new object managed

    return 0;
}