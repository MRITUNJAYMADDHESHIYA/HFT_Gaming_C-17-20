#include<iostream>

template<typename A, typename B, typename C>
void print3(A a, B b, C c){
    std::cout<<a<<" "<<b<<" "<<c<<" "<<std::endl;
}

int main(){
    print3(1,2,3);
    std::string hello = "hello world";
    print3(hello, 2, hello);
    print3(&hello, 2, 3);

}