#ifndef __GENERICOPTION__
#define __GENERICOPTION__

#include<iostream>

//option type call or put
enum OptionType{
    OptionType_Call,
    OptionType_Put
};


class GenericOption{
    public:
        GenericOption(double strike, OptionType type, double cost);
        GenericOption(const GenericOption &p);                      //copy constructor
        ~GenericOption();
        GenericOption &operator = (const GenericOption &p);  //Assignment Operator
        //(It allows one GenericOption object to be assigned to another, copying the values of m_strike, m_type, and m_cost from the right-hand object (p) to the left-hand object.)

        double valueAtExpiration(double underlyingAtExpiration);
        double profitAtExpiration(double underlyingAtExpiration);

    private:
        double     m_strike;
        OptionType m_type;
        double     m_cost;
};

#endif