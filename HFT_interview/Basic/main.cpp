//1.abstraction--->hiding the details which we don't want to show to the user
//an abstract class contains at least one pure virtual function

class Shape{
    public:
        virtual double area() = 0; //pure virtual function
};

class Circle : public Shape{
    double radius;

    public:
        Circle(double r) : radius(r) {}

        double area() override{
            return 3.14 * radius * radius;
        }
};

class Reactangle : public Shape{
    double length, width;

    public:
        Reactangle(double l, double w) : length(l), width(w) {}

        double area() override{
            return length * width;
        }
};

/////// Encapsulation--->Hides data
class BankAccount{
    private:
        double balance;
    public:
        void deposite(double amount){
            balance += amount;
        }

        double getBalance(){
            return balance;
        }
};


//////2.DataType:-
//Primitive ---> char, int, float, long
//Derived -----> array, pointer
//Enumeration---> enum
//User-defined--> struct, class



//////3.static members and static member functions
//Only one copy exists, regardless of how many objects are created

#include<iostream>
using namespace std;

class Employee{
    public:
        static int count; 

        Employee(){
            count++;
        }
};

int Employee::count = 0; //static member function

int main(){
    Employee e1;
    Employee e2;
    Employee e3;

    cout<< Employee::count;
}


///////4.call by value---->we pass a copy of the parameter
//////   call by reference--->we pass the address of the variable 

