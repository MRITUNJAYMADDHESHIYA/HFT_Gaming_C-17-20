#ifndef __INVESTMENT__
#define __INVESTMENT__

#include <iostream>
class Bond{
    public:
        Bond(double principal, double monthlyPayment);
        ~Bond();
        Bond(const Bond &a);
        Bond &operator = (const Bond &a);

        double getMonthlyPayment();
        double getPrincipal();
    private:
        double m_monthlyPay, m_principal;
};

class Mortgage{
    public:
        Mortgage(double monthlyPay, double propertyValue, double downpayment);
        ~Mortgage();
        Mortgage(const Mortgage &a);
        Mortgage &operator = (const Mortgage &a);

        double getMonthlyPayment();
        double getPrincipal();
    private:
        double m_monthlyPay, m_propertyValue, m_downPayment;
};

#endif