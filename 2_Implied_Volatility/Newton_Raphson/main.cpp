#ifndef __MAIN_CPP
#define __MAIN_CPP

#include "black_scholes.h"
#include "newton_raphson.h"
#include <iostream>

int main(int argc, char **argv) {

    double S = 100.0;  
    double K = 100.0;  
    double r = 0.05;   
    double T = 1.0;    
    double C_M = 10.5; 

    // Create the Black-Scholes Call functor
    BlackScholesCall bsc(S, K, r, T);

    // Newton Raphson parameters
    double init = 0.3;  // Our guess impl. vol of 30%
    double epsilon = 0.001;

    // Calculate the implied volatility
    double sigma = newton_raphson<BlackScholesCall, &BlackScholesCall::option_price, &BlackScholesCall::option_vega>(C_M, init, epsilon, bsc);

    std::cout << "Implied Vol: " << sigma << std::endl;

    return 0;
}

#endif