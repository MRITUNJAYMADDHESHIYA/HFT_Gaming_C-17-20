//sring_view :- it's a non-owning view of a string, which means it does not manage the memory of the string it refers to.

#include<iostream>
#include<string_view>
#include<cstdint> //for unit3_t
using namespace std;

static uint32_t alloc = 0;
void* operator new (size_t s){ //operator new is a special function in C++ used to allocate raw memory for objects.
    alloc++;
    cout<<"allocated "<<s<<endl;
    return malloc(s);   //Uses malloc() (from C) to allocate the memory manually.
}

int main(){
    std::string str_1{ "Hello !!, This is CppNuts" };
 
    // std::string str_2{ str_1};
    // std::string str_3{ str_2 };
    
    std::string_view str_2{ str_1.substr(0, 5) };
    std::string_view str_3{ str_2 };
 
    cout << str_1 << '\n'
         << str_2 << '\n'
         << str_3 << '\n';  

    return 0;
}