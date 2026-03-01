// Size of Test comes out to be 24 byte, can you try providing your reasoning behind this??
// This is happening because of padding and here is the reason why padding is important in C++:
// Memory Alignment: It ensures that data types are aligned in memory according to their requirements, which is crucial for optimal access speed on modern processors.
// Performance: Properly aligned data reduces the number of CPU cycles needed for accessing memory, thus enhancing performance.
// Portability: Different compilers and architectures may have varying alignment rules; padding helps maintain consistent behavior across platforms.
// Avoiding Access Errors: Misalignment can lead to hardware exceptions or incorrect data access.
// Overall, padding plays a vital role in ensuring efficient and reliable memory access in C++.

#include<iostream>
class Test{
    public:
        int val1;
        int val2;
        char val3;

        virtual void function(){
            std::cout<<"This is a virtual function "<<std::endl;
        }
};

int main(){
    Test t;
    std::cout<<"SizeOf(t):\t" << sizeof(t) <<std::endl;

    return 0;
}