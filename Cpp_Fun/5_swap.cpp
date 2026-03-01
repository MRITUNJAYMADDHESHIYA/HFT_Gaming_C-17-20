#include<iostream>
#include<utility>
#include<vector>
#include<string>

template<typename T>
void printVectorInfo(const std::vector<T>& V, const std::string& name){
    std::cout<<name<<": ";
    for(auto x: V) std::cout<<x<<" ";
    std::cout<<"\n";
    std::cout<<" size: "<<V.size()<<", Capacity: "<<V.capacity()<<", Data Pointer: "<<V.data()<<"\n\n";
}

int main(){
    std::vector<int> v1{1,2,3};
    std::vector<int> v2{10, 20, 30, 40, 50};

    std::cout<<"Bfore swap:\n";
    printVectorInfo(v1, "v1");
    printVectorInfo(v2, "v2");

    std::swap(v1, v2);

    std::cout<<"After swap:\n";
    printVectorInfo(v1, "v1");
    printVectorInfo(v2, "v2");

    return 0;
}