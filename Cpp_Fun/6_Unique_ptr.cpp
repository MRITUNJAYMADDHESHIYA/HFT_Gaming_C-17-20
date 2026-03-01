#include<iostream>
using namespace std;

//Only one unique_ptr can own a given object at a time.
//Cannot copy a unique_ptr. Prevents double deletion.
//Ownership can be transferred using std::move.
template<typename T>
class UniquePointer{
    private:
        T* ptr;
    public:
        explicit UniquePointer(T* p = nullptr) : ptr(p){
            cout<<"Constructor called\n";
        }

        ~UniquePointer(){
            delete ptr;
            cout<<"Destructor called\n";
        }

        //delete copy operations
        UniquePointer(const UniquePointer&) = delete;
        UniquePointer& operator=(const UniquePointer&) = delete;

        //move constructor
        UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr){
            cout<<"Move constructor called\n";
            other.ptr = nullptr;
        }

        //move assignment operator
        UniquePointer& operator=(UniquePointer&& other) noexcept{
            cout<<"Move assignment called\n";
            if(this != &other){
                delete ptr;       //clean up current resource
                ptr  = other.ptr; // take ownership
                other.ptr = nullptr;
            }
            return *this;
        }

        T* operator->() {return ptr;} //for pointer
        T& operator*() {return *ptr;} //for object

        //for checking if empty
        operator bool() const {return ptr != nullptr;}
};

class Demo{
    public:
        Demo() {cout<<"Demo created\n";}
        ~Demo(){cout<<"Demo destroyed\n";}
        void hello(){cout<<"Hello from Demo!\n";}
};

int main(){
    cout<<"=== Move Constructor Example ===\n";
    UniquePointer<Demo> up1(new Demo());
    UniquePointer<Demo> up2 = std::move(up1);//calls move constructor

    if(!up1){
        std::cout<<"up1 is emplty!"<<std::endl;
    }

    cout<<"\n === Move Assignement Example ===\n";
    UniquePointer<Demo> up3(new Demo());
    UniquePointer<Demo> up4(new Demo());
    up4 = std::move(up3); //calls move assigment
    if(!up3){
        std::cout<<"up3 is empty!"<<std::endl;
    }

    cout<<"\n ===End of main ===\n";
    return 0;
}