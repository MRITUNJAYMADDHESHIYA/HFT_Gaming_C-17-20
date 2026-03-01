#include "Bionomial.hpp"
#include<iostream>


BinomialModel::BinomialModel(double T, double S, double r,double sigma,double q,int n, bool call):
    m_T(T),
    m_S(S),
    m_r(r),
    m_sigma(sigma),
    m_n(n),
    m_q(q),
    m_call(call)
{}
BinomialModel::BinomialModel(const BinomialModel &p):
    m_T(p.m_T),
    m_S(p.m_S),
    m_r(p.m_r),
    m_sigma(p.m_sigma),
    m_n(p.m_n),
    m_q(p.m_q),
    m_call(p.m_call)
{}
BinomialModel::~BinomialModel()
{}
BinomialModel &BinomialModel::operator=(const BinomialModel &p){
    if (this != &p){
        m_T = p.m_T;
        m_S = p.m_S;
        m_r = p.m_r;
        m_sigma = p.m_sigma;
        m_n = p.m_n;
        m_q = p.m_q;
        m_call = p.m_call;
    }
    return *this;
}

void BinomialModel::computerPriceStep(int i, int j, double k, vec &prices, double p_u, double p_d, double u){
    prices[i] = p_u*prices[i] + p_d*prices[i+1];
}

double BinomialModel::optionPriceForStrike(double k){
    double delta = m_T/m_n; //size of each steps
    double u = exp(m_sigma *sqrt(delta));

    double p_u = (u*exp(-m_r*delta) - exp(-m_q*delta)) * u / (u*u -1);
    double p_d = exp(-m_r*delta) - p_u;

    vec prices(m_n);

    
    // stock price at the last level of the binomial tree.
    for(int i=0; i<m_n; i++){
        if(m_call){
            prices[i] = std::max(0.0, m_S*pow(u, 2*i - m_n) - k);
        }else{
            prices[i] = std::max(0.0, k-m_S*pow(u,2*i - m_n));
        }
    }
    
    //travel last to root
    for(int j=m_n-1; j>=0; j--){
        for(int i=0; i<j; i++){
            computerPriceStep(i,j,k,prices, p_u, p_d, u);
        }
    }
    return prices[0];
}