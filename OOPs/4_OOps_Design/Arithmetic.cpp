#include<iostream>
#include<type_traits>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
class Calculator{
    private:
        T value;

    public:
        Calculator(T value): value(value){}

        T add(T other)const {
            return value + other;
        }

        T subtract(T other)const{
            return value - other;
        }
};

int main(){
    Calculator<int> Cal(10);
    std::cout<< "Addition: "<< Cal.add(5) << std::endl;
    std::cout<< "Substraction: "<< Cal.subtract(3) <<std::endl;

    return 0;
}