#include<iostream>
#include<vector>
#include<cmath>
#include<numeric>

//cumulative normal distributionfunction
double Gauss(double x){
    return 0.5 * (1.0 + erf(x / std::sqrt(2.0)));
}

//Black-Scholes price calculation
double bs_price(double S, double K, double r, double T, double V, const std::string& PutCall){
    double d1 = (std::log(S/K) + (r+0.5*V*V)*T)/(V* std::sqrt(T));
    double d2 = d1 - V * std::sqrt(T);
    double bs_call = S * Gauss(d1) - K * std::exp(-r*T) * Gauss(d2);

    if(PutCall == "Call"){
        return bs_call;
    }else{
        return bs_call - S + k * std::exp(-r * T);
    }
}

//compute weights for options
std::vector<double> ComputeWeight(double Spot, double Sb, double r, double timeToMaturity, const std::vector<double>&V, const std::)