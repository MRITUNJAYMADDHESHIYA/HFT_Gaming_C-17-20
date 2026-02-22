#ifndef __MAIN_CPP
#define __MAIN_CPP

#include "black_scholes.h"
#include "interval_bisection.h"
#include <iostream>

int main(int argc, char **argv){

    double S = 100.0;
    double K = 100.0;
    double r = 0.05;
    double T = 1.0;
    double C_M = 10.5;

    BlackScholesCall bsc(S, K, r, T);

    //interval bisection parameters
    double low_vol  = 0.05;
    double high_vol = 0.35;
    double episilon = 0.001;

    //calculate the implied valatility
    double sigma = interval_bisection(C_M, low_vol, high_vol, episilon, bsc);

    std::cout<<"Implied Vol: " <<sigma <<std::endl;

    return 0;
}

#endif