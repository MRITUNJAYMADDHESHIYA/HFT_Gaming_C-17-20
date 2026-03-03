#include "volatility.h"
#include <iostream>


int main(int argc, const char* argv[]){
    double price;
    Volatility v;
    for(;;){
        std::cin >> price;
        if(price == -1){
            break;
        }
        v.addPrice(price);
    }

    std::cout<<"range volatility is "<<v.rangeVolatility()<<std::endl;
    std::cout<<"average daily range is "<<v.avgDailyRange() <<std::endl;
    std::cout<<"standard deviation is "<<v.stdDev()<<std::endl;
    return 0;
}