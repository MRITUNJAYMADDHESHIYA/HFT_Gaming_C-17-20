#include<iostream>

//1.Static inside a function
//(A static variable inside a function is created only once, and its value persists even after the function return)
void counter(){
    static int count = 0;
    count++;
    std::cout<< count << std::endl;
}

int main(){
    counter(); //1
    counter(); //2
    counter(); //3

    return 0;
}



//2.Static data members
class Employee{
    private:
        static int count; //static data member
    public:
        Employee(){
            count++;
        }
        static void showCount(){ //static member function
            std::cout<<"Number of Employees: "<< count << std::endl;
        }
};

int Employee::count = 0; //definition of static data member

int main(){
    Employee e1;
    Employee e2;
    Employee e3;

    Employee::showCount(); //accessing static member function without creating object

    return 0;
}