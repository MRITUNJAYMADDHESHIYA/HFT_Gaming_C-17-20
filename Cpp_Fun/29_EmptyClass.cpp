#include<iostream>

class Empty {};

int main(){
    Empty a, b;
    std::cout<< sizeof(Empty) << '\n';
    std::cout<< (&a == &b) << '\n';
}
//1byte because of two object does not have same address
//output:- 1 0
