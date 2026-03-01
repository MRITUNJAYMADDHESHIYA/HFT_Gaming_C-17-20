#include<iostream>

int main(){

    int var = 20;

    const int* varptr = &var;

    int* value = const_cast<int*>(varptr);

    std::cout<<"original value:"<<var<<std::endl;
    *value = 30;
    std::cout<<"value after change:"<<*value<<std::endl;

    return 0;
}