#include "MA.h"
#include<iostream>

int main(int argc, const char* argv[]){
    if(argc != 2){
        std::cout<<"usage: progName <num periods>"<<std::endl;
        return 1;
    }

    int num_periods = atoi(argv[1]);
    double price;
    MA calculator(num_periods);
    for(;;){
        std::cin>>price;
        if(price == -1){
            break;
        }
        calculator.addPriceQuote(price);
    }

    std::vector<double> ma =calculator.SMA();
    for(int i=0; i<ma.size(); ++i){
        std::cout<<"average value "<<i <<"="<< ma[i] <<std::endl;
    }

    std::vector<double> ema = calculator.EMA();
    for(int i=0; i<ema.size(); ++i){
        std::cout<<"exponential value: "<< i <<"= "<<ema[i] <<std::endl;
    }
    return 0;
}