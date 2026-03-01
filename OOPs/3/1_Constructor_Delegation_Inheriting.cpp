//Constructor delegation:- enables one constructor to call another constructor in the same class.
//Inheriting constructors:- allows a derived class to use the base class's constructors directly

#include<iostream>
#include<string>

class Person{
    private:
        std::string name;
        int age;
    public:
        Person(): Person("Unknown", 0) {} //constructor
        Person(const std::string& name, int age): name(name), age(age) {}

        void display() const{
            std::cout<<"Name: "<<name<< ", Age: "<<age<<std::endl;
        }
};

class Base{
    private:
        int x;
        double y;
    public:
        Base(int x, double y): x(x), y(y) {}
        Base(const std::string& str): x(str.length()), y(0.0){}

        void display() const{
            std::cout<<"Base x: "<< x << ", y: "<<y << std::endl;
        }
};

class Derived : public Base{
    public:
        using Base::Base; //Inherit constructor from base
};


int main(){
    Person person1; //use default constructor
    Person person2("Mrity", 23); //use parameterized constructor

    person1.display();
    person2.display();


    Derived d1(42, 3.14);
    Derived d2("Hello");

    d1.display();
    d2.display();

    return 0;
}


