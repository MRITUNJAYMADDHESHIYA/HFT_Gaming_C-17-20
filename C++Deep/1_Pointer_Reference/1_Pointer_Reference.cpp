#include<iostream>
#include<string>
#include<string_view> //No copying of string data(just a pointer to fist character and a length)


class Animal{
    protected:
        std::string name;
        Animal(std::string_view name): name{name} {} //constructor

        Animal(const Animal&) = delete;             //copy constructor
        Animal& operator=(const Animal&) = delete;  //copy assignment operator
    public:
        std::string_view getName() const { return name; }
        std::string_view speak() const { return "???"; }
};

class Cat: public Animal{
    public:
        Cat(std::string_view name): Animal{name} {}
        std::string_view speak() const { return "Meow"; }
};

class Dog: public Animal{
    public:
        Dog(std::string_view name): Animal{name} {}
        std::string_view speak() const {return "Woof"; }
};


int main(){
    const Cat cat{ "Fred" };
    std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';
    
    const Dog dog{ "Garbo" };
    std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

    const Animal* pAnimal{ &cat }; //pointer to base class pointing to derived class object
    std::cout<< "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    pAnimal = &dog; //pointing to another derived class object
    std::cout<< "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    return 0;
}
