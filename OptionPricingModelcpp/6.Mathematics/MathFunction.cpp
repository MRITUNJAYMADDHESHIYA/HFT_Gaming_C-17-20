#include "MathFunction.hpp"
#include<iostream>
using namespace std;

Polynomial::Polynomial(const vector<double> &coefficient):
    m_coefficient(coefficient)
{}
Polynomial::Polynomial(const Polynomial &p):
    m_coefficient(p.m_coefficient)
{}
Polynomial::~Polynomial()
{}
Polynomial &Polynomial::operator=(const Polynomial &p){
    if(this != &p){
        m_coefficient = p.m_coefficient;
    }
    return *this;
}

double Polynomial::operator()(double x){
    int n = (int)m_coefficient.size();
    double y=0;
    int i;
    for(i=0; i<n-1; i++){
        y += m_coefficient[i];
        y *= x;
    }

    if(i<n){
        y += m_coefficient[i];
    }
    return y;
}

int main(){
    Polynomial f({ 1, 0, 0 });
    double begin = -2, end = 2;
    double step = (end - begin) / 100.0;

    for (int i=0; i<100; ++i){
        cout <<  begin + step * i << ", ";
    }
    cout << endl;
    for (int i=0; i<100; ++i){
        cout << f( begin + step * i) << ", ";
    }
    return 0;
 }