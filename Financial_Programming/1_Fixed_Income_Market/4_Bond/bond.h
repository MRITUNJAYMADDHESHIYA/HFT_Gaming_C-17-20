#ifndef __BONDS__
#define __BONDS__

#include<iostream>

class Bond{
    public:
        Bond(const std::string institution, int numPeriods, double principal, double couponValue);
        Bond(const Bond &v);
        Bond &operator = (const Bond &v);
        ~Bond();

        double interestRate();
    private:
        std::string m_institution;
        double m_principal;
        double m_coupon;
        int m_numPeriods;
};

#endif
