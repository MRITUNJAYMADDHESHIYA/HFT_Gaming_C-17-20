#include<iostream>
#include<type_traits>

//calculation for arithmetic types
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
class Calculator{
    public:
        Calculator(T value): value(value) {}

        T add(T other) const {
            return value + other;
        }

        T subtract(T other) const{
            return value - other;
        }

    private:
        T value;
};

int main(){
    Calculator<int> intCalc(10);
    std::cout<<"Addition: "<<intCalc.add(5) <<std::endl;
    std::cout<<"Substraction: "<<intCalc.subtract(3)<<std::endl;

    return 0;
}