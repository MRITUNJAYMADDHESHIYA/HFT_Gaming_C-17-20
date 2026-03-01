#include "bond.h"

Bond::Bond(const std::string institution, int numPeriods, double principle, double couponValue): m_institution(institution), m_numPeriods(numPeriods), m_principal(principle), m_coupon(couponValue) {}
Bond::Bond(const Bond &v):m_institution(v.m_institution),m_numPeriods(v.m_numPeriods),m_principal(v.m_principal),m_coupon(v.m_coupon){}
Bond::~Bond(){}
Bond &Bond::operator=(const Bond &v){
    if(this != &v){
        this->m_institution = v.m_institution;
        this->m_principal   = v.m_principal;
        this->m_numPeriods  = v.m_numPeriods;
        this->m_coupon      = v.m_coupon;
    }
    return *this;
}

double Bond::interestRate(){
    return m_coupon / m_principal;
}

