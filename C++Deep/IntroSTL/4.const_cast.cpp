#include<iostream>

int main(){
    // int x = 10;
    // const int* valptr = &x;    //reference


    // int* value = const_cast<int*>(valptr);  //using const_cast we can change the value of x
    // *value = 20;

    // std::cout<<x<<std::endl;
    // std::cout<<*value<<std::endl;
    // return 0;
 
    /////////////////////failure of const_cast/////////////////
    const int x = 10;          //if we are using const
    const int* valptr = &x;    //reference


    int* value = const_cast<int*>(valptr);  //using const_cast we can change the value of x
    *value = 20;              //we can not change the value of x

    std::cout<<x<<std::endl;  //10
    std::cout<<*value<<std::endl; //20
    return 0;
}