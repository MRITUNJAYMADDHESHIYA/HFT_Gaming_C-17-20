#include "compound.h"
#include<cmath>

CompoundIntRate::CompoundIntRate(double rate) : m_rate(rate) {}
CompoundIntRate::~CompoundIntRate() {}
CompoundIntRate::CompoundIntRate(const CompoundIntRate &v) : m_rate(v.m_rate) {}
CompoundIntRate &CompoundIntRate::operator=(const CompoundIntRate &v){
    if(this != &v){
        this->m_rate = v.m_rate;
    }
    return *this;
}

double CompoundIntRate::multiplePeriod(double value, int numPeriods){
    double f = value * pow(1 + m_rate, numPeriods);
    return f;
}

double CompoundIntRate::continuousCompounding(double value, int numPeriods){
    double f = value * exp(m_rate * numPeriods);
    return f;
}

