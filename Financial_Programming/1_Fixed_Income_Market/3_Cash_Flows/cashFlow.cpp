#include "cashFlow.h"
#include <cmath>
#include <iostream>

CashFlow::CashFlow(double rate): m_rate(rate) {}
CashFlow::CashFlow(const CashFlow &v): m_rate(v.m_rate) {}
CashFlow::~CashFlow(){}
CashFlow &CashFlow::operator=(const CashFlow & v){
    if(this != &v){
        this->m_cashPayments = v.m_cashPayments;
        this->m_timePeriods  = v.m_timePeriods;
        this->m_rate         = v.m_rate;
    }
    return *this;
}


void CashFlow::addCashPayment(double value, int timePeriod){
    m_cashPayments.push_back(value);
    m_timePeriods.push_back(timePeriod);
}

double CashFlow::presentValue(double fututeValue, int timePeriod){
    double pValue = fututeValue / pow(1+m_rate, timePeriod);
    std::cout<<" Value "<<pValue << std::endl;
    return pValue;
}

double CashFlow::presentValue(){
    double total = 0;
    for(int i=0; i<m_cashPayments.size(); i++){
        total += presentValue(m_cashPayments[i], m_timePeriods[i]);
    }
    return total;
}

