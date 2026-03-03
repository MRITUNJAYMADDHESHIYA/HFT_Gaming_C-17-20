#include "volatility.h"
#include <iostream>
#include <cmath>

Volatility::Volatility(){}
Volatility::~Volatility(){}
Volatility::Volatility(const Volatility &v):m_prices(v.m_prices){}
Volatility &Volatility::operator=(const Volatility &v){
    if(&v != this){
        m_prices = v.m_prices;
    }
    return *this;
}

void Volatility::addPrice(double price){
    m_prices.push_back(price);
}

double Volatility::rangeVolatility(){
    if(m_prices.size() < 1){
        return 0;
    }
    double min = m_prices[0];
    double max = min;

    for(int i=1; i<m_prices.size(); i++){
        if(m_prices[i] < min){
            min = m_prices[i];
        }
        if(m_prices[i] > max){
            max = m_prices[i];
        }
    }
    return max - min;
}

double Volatility::avgDailyRange(){
    unsigned long n = m_prices.size();
    if(n < 2){
        return 0;
    }
    double previous = m_prices[0];
    double sum = 0;
    for(int i=1; i<m_prices.size(); ++i){
        double range = abs(m_prices[i] - previous);
        sum += range;
    }
    return sum / n-1;
}

double Volatility::mean(){
    double sum = 0;
    for(int i=0; i<m_prices.size(); i++){
        sum += m_prices[i];
    }
    return sum / m_prices.size();
}

double Volatility::stdDev(){
    double m = mean();
    double sum = 0;
    for(int i=0; i<m_prices.size(); i++){
        double val = m_prices[i] - m;
        sum += val * val;
    }
    return sqrt(sum / (m_prices.size() - 1));
}

