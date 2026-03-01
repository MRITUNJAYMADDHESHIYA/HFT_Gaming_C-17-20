#ifndef MathFunction_hpp
#define MathFunction_hpp

#include<stdio.h>
#include<vector>
using namespace std;

class MathFunction{
    public:
        virtual ~MathFunction(){}
        virtual double operator()(double x) = 0;
    private:
        //interface
};

///polynomial = c1x^n + c2x^n-1 +.....
class Polynomial : public MathFunction{
    public:
        Polynomial(const vector<double> &coefficient);
        Polynomial(const Polynomial &p);
        virtual ~Polynomial();
        Polynomial &operator=(const Polynomial &p);

        virtual double operator()(double x) override;
        vector<double> m_coefficient;
};
#endif