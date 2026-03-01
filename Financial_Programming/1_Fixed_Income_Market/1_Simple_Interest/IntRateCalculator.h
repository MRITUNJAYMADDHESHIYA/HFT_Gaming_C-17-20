#ifndef __FinancialSamples__IntRateCalculator__
#define __FinancialSamples__IntRateCalculator__

#include <iostream>

class IntRateCalculator{
    public:
        IntRateCalculator(double rate);
        IntRateCalculator(const IntRateCalculator &v);
        IntRateCalculator &operator = (const IntRateCalculator &v);
        ~IntRateCalculator();

        double singlePeriod(double value);
    private:
        double m_rate;
};

//simple formula :- V = P (1 + R)
//inline use in header file
inline double IntRateCalculator::singlePeriod(double present_value){
    double future_value = present_value * (1 + this->m_rate);
    return future_value;
}

#endif