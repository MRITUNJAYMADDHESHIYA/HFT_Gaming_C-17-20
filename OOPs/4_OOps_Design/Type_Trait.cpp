#include<iostream>
#include<type_traits>

//1.“A compile-time contract between the template and the type you pass in.”
//2.Improve template improve
template<typename T>
concept Printable = requires(std::ostream& os, T t){
    {os << t}-> std::same_as<std::ostream&>;
};

template<Printable T>
void print(const T& value){
    std::cout<<value<<std::endl;
}

int main(){
    print(23);
    print(3.52);
    print("Mritunjay");

    return 0;
}