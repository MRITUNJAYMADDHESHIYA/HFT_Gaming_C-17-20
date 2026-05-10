//1.Compilation model ==== preprocessing(#include) + compilation() + linking
//2.Translation unit  ==== main.cpp + all included headers
//3.Header files      ==== declarations + templates + inline + class +constants
//4.include guards    ==== avoid same header
#ifndef MATH_H
#define MATH_H
#endif
//or
#pragma once

//5.ODR(one definition rule)  ==== variables/function + classes/types/templates + inline functions +  
/////declaration(something exists) + definition(actually created it)



//////// Stack vs Heap ///////////////////////////////////
//stack
//1.automatic memory
//2.data-type(int, char, double) store and no manual cleanup needed
//3.every function call creates a stack frame
//4.compile time
//5.faster


//heap
//1.dynamic memory + 
//2.new + malloc , delete
//3.runtime
//4.slower === searching free memory + fragmentation + allocator + synchronization


int* p = new int(5);
//stack: p   + heap:5

class A{
    public:
        A(){std::cout<<"Constructor";}
        ~A(){std::cout<<"Destructor";}
};
int main(){
    A  obj1;            //stack
    A* obj2 = new A();  //heap
    delete obj2;
}


///////// Memory layout of a C++ program /////////////////

int global_init = 10;        //data segment
static global_init2 = 5;     //data segment

int global_uninit;           //BSS segment (block started by symbol)
static global_uninit2;       //BSS segment

const char* msg = "Hello";   //RODATA(read-only data segment)

void func(){
    int local = 5;               //stack segment
    int* p = new int(5);         //heap segment

    delete p;
}

///why are globals initialized to zero? --> BSS is zeroed by OS loader


//////////////////  Const (thread safety + compiler optimization )///////////////////////
//1.const variables
//2.pointers
//3.const reference
//4.const member functions
//5.const objects
//6.mutable---->using this i can modify it
//7.const retrun types


const int x = 10;   //can't be modify

//pointer to const
const int* p;
int const* p;    //data is cont + pointer is mutable


//const pointer
int* const p = &x; //data is mutable + pointer is const


//const pointer to const data
const int* const p = &x;  //both fixed

////reference
void print(std::string s){}
void print(const std::string& s) {} //no copy + can't modify 

///const member
class A{
    int x;

    public:
        int getX() const{
            return x;
        }
};

//const objects
const A obj;
class A{
    public:
        void f() {}
        void g() const {}
};

const A a;
a.g(); //ok
a.f(); //error


//////mutable
class logger{
    mutable int count = 0;

    public:
        void log() const{
            ++count;
        }
};


///////////////////// Referance vs Pointer ////////////////////////
//Reference:-(another name of same object)
//canot be null






//Pointer:-(object address)
//can be nullptr


int a = 1;
int b = 2;

int* p = &a;
p = &b;     //i can change in pointer

int& r = a;
r = b;   //i can't

//array
void f(int* arr){}   //no array size information
void f(int(&arr)[N]){} //exact size and type

//function return
int& f(){
    int x = 5;
    return x;
}///dangling reference --->undefined behavior

//references in classes
class A{
    int& ref;
};


/////////////////////// lvalue vs rvalue ///////////////////////////
//lvalue:-  <---- glvalue(generalized Lvalue) ---> xvalue(expiring value)
//has identifiable memory location




//rvalue:- ---->prvalue(pure right value)
//temporary value
//rvalue have no memory

int x = 10; //x-->lvalue   + 10 -->rvalue

int& r = x; //ok
int& r = 5; //error

const int& r = 5;  //compiler creates temporary object

std::vector<int> v1 = {1,2,3};
std::vector<int> v2 = std::move(v1);  //converts to rvalue(moving instead of copying)


void f(int& x){
    std::cout<<"lvalue";
}
void f(int&& x){
    std::cout<<"rvalue";
}

int a = 5;
f(a); //lvalue
f(5); //rvalue



////////////////////// move semantics ////////////////////////////
//steal internal pointer

class Buffer{
    int* data;
    size_t size;

    public:
        Buffer(size_t n) : size(n){
            data = new int[n];
        }

        ~Buffer(){
            delete[] data;
        }

        //move constructor
        Buffer(Buffer&& other): data(other.data), size(other.size){
            other.data = nullptr;
            other.size = 0;
        }

        //move assignment operator
        Buffer& operator=(Buffer&& other){
            if(this != &other){
                delete[] data;

                data = other.data;
                size = other.size;

                other.data = nullptr;
                other.size = 0;
            }
            return *this;
        }
};












