#include "correlation.h"
#include "timeSeries.h"

#include <iostream>

int main(int argc, const char* argv[]){
    double price;
    TimeSeries tsa;
    TimeSeries tsb;
    for(;;){
        std::cin>> price;
        if(price == -1){
            break;
        }
        tsa.addValue(price);
        std::cin >> price;
        tsb.addValue(price);
    }
    Correlation c(tsa, tsb);
    auto correlation = c.correlation();
    std::cout<< "Correlation is "<< correlation << std::endl;
    return 0;
}