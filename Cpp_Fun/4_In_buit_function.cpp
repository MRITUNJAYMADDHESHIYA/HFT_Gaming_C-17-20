//std::reverse()
//member .reverse()


////list
// Fast insertion/deletion at any position (especially middle)
// No random access (unlike std::vector)
// Bidirectional iterator support
// Automatically handles memory management for nodes

#include<iostream>
#include<list>
#include<algorithm>

class CopyOnly{
    public:
        int value;         //data membar
        CopyOnly(int v):value(v){}    //constructor which initializes the value membar

        CopyOnly(const CopyOnly& other) : value(other.value){ //copy constructor
            std::cout<<"Copy Constructor\n";
        }

        CopyOnly& operator=(const CopyOnly& other){
            value = other.value;
            std::cout<<"Copy assignment\n";
            return *this;
        }

        CopyOnly(CopyOnly&&) = delete;
        CopyOnly& operator=(CopyOnly&&) = delete;

        //swap function
        friend void swap(CopyOnly& a, CopyOnly& b){ //friend access private or protected members
            std::cout<<"Custom swap using copies\n";
            CopyOnly temp = a;//copy constructor
            a = b;            //copy assignment
            b = temp;         //copy assignment
        }
};

int main(){
    std::list<CopyOnly> lst;
    lst.emplace_back(1);
    lst.emplace_back(2);
    lst.emplace_back(3);

    //std::reverse(lst.begin(), lst.end());
    lst.reverse();

    for(const auto& ele: lst){
        std::cout<< ele.value<<" ";
    }
    std::cout<< "\n";
}