#include "investment.h"

Bond::Bond(double principal, double monthlyPayment) : m_principal(principal), m_monthlyPay(monthlyPayment){}
Bond::~Bond(){}
Bond::Bond(const Bond &a) : m_monthlyPay(a.m_monthlyPay), m_principal(a.m_principal){}
Bond &Bond::operator=(const Bond &a){
    if(this != &a){
        m_principal = a.m_principal;
        m_monthlyPay = a.m_monthlyPay;
    }
    return *this;
}

double Bond::getMonthlyPayment(){
    return m_monthlyPay;
}
double Bond::getPrincipal(){
    return m_principal;
}


Mortgage::Mortgage(double monthlyPay, double propertyValue, double downpayment) : m_monthlyPay(monthlyPay), m_propertyValue(propertyValue), m_downPayment(downpayment) {}
Mortgage::~Mortgage(){}
Mortgage::Mortgage(const Mortgage &a):m_downPayment(a.m_downPayment), m_propertyValue(a.m_propertyValue), m_monthlyPay(a.m_monthlyPay){}
Mortgage &Mortgage::operator=(const Mortgage &a){
    if(this != &a){
        m_downPayment = a.m_downPayment;
        m_propertyValue = a.m_propertyValue;
        m_monthlyPay  = a.m_monthlyPay;
    }
    return *this;
}

double Mortgage::getMonthlyPayment(){
    return m_monthlyPay;
}
double Mortgage::getPrincipal(){
    return m_propertyValue - m_downPayment;
}