#include<string>
#include<iostream>
using namespace std;

enum CDSUnderlying {
    CDSUnderlying_Bond,
    CDSUnderlying_Cash,
};

enum Date{
};

//Encapsulation
class CDSContract {
    public:
        CDSContract();
        CDSContract(const CDSContract &p);
        ~CDSContract();
        CDSContract &operator=(const CDSContract &p);

        //acess the private components allow the counterpart and payoff member 
        std::string counterpart(){return m_counterpart;}
        void setCounterpart(const std::string &s){m_counterpart = s;}
        double payoff(){return m_payoff;}
        void setPayoff(double payoff){m_payoff = payoff;}

        virtual double computerCurrentValue(const Date &d); //polymorphism

    private:
        std::string m_counterpart;
        CDSUnderlying m_underlying;
        double m_payoff;
        int m_term;
        double m_spreadCost;
};

//Inheritance
//I can acess ths CDSContract class in this class
class LoanOnlyCDSContracr : public CDSContract{
    public:
        void changeLoanSource(const std::string &source);
    private:
        std::string m_loanSource;
};

//polymorphism(virtual methods)
// the polymorphic call mechanism will determine the correct implementation for the member 
// function, depending on the exact class of the instance pointed to by the contract 
// pointer. 

//Virtual Table:-
// polymorphism allows for more flexible and dynamic behavior in OOP, enabling code reuse and extensibility. 
// Virtual tables (vtables) are the underlying mechanism that supports runtime polymorphism by associating 
// function calls with the correct method implementations based on the actual object type, rather than the
//  reference type, ensuring that overridden methods are properly invoked at runtime.


//destructor use for class and also for virtual function
// Once a virtual destructor has been declared in the base class, all descendant classes 
// will also contain a virtual destructor, independent of using the virtual keyword. This 
// is guaranteed by the presence of a virtual table containing the address of the destructor
class CDSContract {
    public:
        CDSContract() {}
        CDSContract(const CDSContract &p);
        virtual ~CDSContract() { std::cout << " base delete " << std::endl; }
        CDSContract &operator=(const CDSContract &p);
        
};


//Object Composition:-
class MathIntegration;
class CDSContract {
    public:
        CDSContract() {}
        CDSContract(MathIntegration *mipt); // by passing to the CDSContract constructor a pointer to a 
        //MathIntegration object and storing that pointer as a member function.
        CDSContract(const CDSContract &p);
        virtual ~CDSContract() { std::cout << " base delete " << std::endl; }
        CDSContract &operator=(const CDSContract &p);
    
    private:
        std::string m_counterpart;
        CDSUnderlying m_underlying;
        double m_payoff;
        int m_term;
        double m_spreadCost;
        MathIntegration *m_mipt;
        static double kStandardPayoff;
 };