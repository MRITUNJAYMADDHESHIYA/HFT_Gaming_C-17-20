#include<iostream>
#include<string_view>

//1.without virtual:- Static binding (function chosen based on reference type)
//2.with virtual   :- Dynamic binding(function chosen based on actual object type)
class Base{
    public:
        std::string_view getName() const {return "Base";}
};

class Derived: public Base{
    public:
        std::string_view getName() const {return "Derived";}
};

int main(){
    Derived derived {};    //it contain both its own data + base subobject
    Base& rBase{derived};  //rBase refers to the Base part of the derived object
    
    std::cout<< "rBase is a: "<< rBase.getName() << '\n'; //output Base

    return 0;
}

//////////////////////////////////////////
class Base{
    public:
        virtual std::string_view getName() const {return "Base";}

        virtual ~Base() = default; //for modern compiler
};

class Derived: public Base{
    public:
        std::string_view getName() const {return "Derived";}
};

int main(){
    Derived derived {};    //it contain both its own data + base subobject
    Base& rBase{derived};  //rBase refers to the Base part of the derived object
    
    std::cout<< "rBase is a: "<< rBase.getName() << '\n'; //output Derived

    return 0;
}





//////////////////////
//not studyd yet so meet tommorow