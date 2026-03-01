#ifndef __PAY_OFF_CPP
#define __PAY_OFF_CPP

#include "payoff.h"

PayOff::PayOff(){}

//PayOffCall
//Constructor with single strick parameter
PayOffCall::PayOffCall(const double& _K) {K = _K;}

double PayOffCall::operator() (const double& S) const{
    return std::max(S-K, 0.0);
}

//PayOffPut
PayOffPut::PayOffPut(const double& _K){K = _K;}

double PayOffPut::operator()(const double& S) const{
    return std::max(K-S, 0.0);
}

#endif