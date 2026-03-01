//1.Null pointer
//A pointer that does not point to any valid memory location
int* p = nullptr; 


//2.Wild pointer
//A pointer that has not been initialized and may point to any random memory location
int* q; 


//////////////3.Dangling pointer
//A pointer that points to a memory location that has been freed or deallocated
int* r = new int(10);
delete r;
std::cout<<*r;

//returning address of local variable
int* fun(){
    int x = 10;
    return &x; //dangling pointer
}

//double delete pointer
int * s = new int(20);
delete s;  
delete s; // undefined behavior
//how to avoid double delete
s = nullptr;