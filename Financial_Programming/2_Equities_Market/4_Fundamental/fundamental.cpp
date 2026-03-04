#include "fundamental.h"
#include <iostream>

Fundamental::Fundamental(const std::string &ticker, double price, double dividend):
m_ticker(ticker),
m_price(price),
m_dividend(dividend),
m_earningsEstimate(0),
m_numShares(0),
m_bookValue(0),
m_assets(0),
m_liabilitiesAndIntangibles(0),
m_epsGrowth(0),
m_netIncome(0),
m_shareholdersEquity(0)
{}

Fundamental::Fundamental(const Fundamental &v):
m_ticker(v.m_ticker),
m_price(v.m_price),
m_dividend(v.m_dividend),
m_earningsEstimate(v.m_earningsEstimate),
m_numShares(v.m_numShares),
m_bookValue(v.m_bookValue),
m_assets(v.m_assets),
m_liabilitiesAndIntangibles(v.m_liabilitiesAndIntangibles),
m_epsGrowth(v.m_epsGrowth),
m_netIncome(v.m_netIncome),
m_shareholdersEquity(v.m_shareholdersEquity)
{}

Fundamental::~Fundamental() {}
Fundamental &Fundamental::operator=(const Fundamental &v){
    if(this != &v){
        m_ticker = v.m_ticker;
        m_price = v.m_price;
        m_dividend = v.m_dividend;
        m_earningsEstimate = v.m_earningsEstimate;
        m_numShares = v.m_numShares;
        m_bookValue = v.m_bookValue;
        m_assets = v.m_assets;
        m_liabilitiesAndIntangibles = v.m_liabilitiesAndIntangibles;
        m_epsGrowth = v.m_epsGrowth;
        m_netIncome = v.m_netIncome;
        m_shareholdersEquity = v.m_shareholdersEquity;
    }
    return *this;
}


double Fundamental::PE(){
    return (m_price * m_numShares) / m_earnings;
}

double Fundamental::forwardPE(){
    return (m_price * m_numShares) / m_earningsEstimate;
}

double Fundamental::returnOnEquity(){
    return m_netIncome / m_shareholdersEquity;
}

double Fundamental::getDividend(){
    return m_dividend;
}

double Fundamental::bookValue(){
    return m_bookValue;
}

double Fundamental::priceToBookRatio(){
    return (m_price * m_numShares) / (m_assets - m_liabilitiesAndIntangibles);
}

double Fundamental::priceEarningsToGrowth(){
    return PE() / m_epsGrowth;
}

void Fundamental::setNumOfShare(int n){
    m_numShares = n;
}

void Fundamental::setEarnings(double val){
    m_earnings = val;
}

void Fundamental::setExpectedEarnings(double val){
    m_earningsEstimate = val;
}

void Fundamental::setBookValue(double val){
    m_bookValue = val;
}

void Fundamental::setEpsGrowth(double val){
    m_epsGrowth = val;
}

void Fundamental::setNetIncome(double val){
    m_netIncome = val;
}

void Fundamental::setShareHoldersEquity(double val){
    m_shareholdersEquity = val;
}

void Fundamental::setLiabilitiesAndIntangibles(double val){
    m_liabilitiesAndIntangibles = val;
}

void Fundamental::setAssets(double val){
    m_assets = val;
}

