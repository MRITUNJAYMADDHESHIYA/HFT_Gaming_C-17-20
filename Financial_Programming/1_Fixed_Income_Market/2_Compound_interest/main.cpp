#include "compound.h"
#include<iostream>

int main(int argc, const char* argv[]){
    if(argc != 4){
        std::cout<<"usage: progName <interest rate> <present value> <num periods>" <<std::endl;
        return 1;
    }

    double rate = atof(argv[1]);
    double value = atof(argv[2]);
    int num_periods = atoi(argv[3]);

    CompoundIntRate cr(rate);
    double res = cr.multiplePeriod(value, num_periods);
    double contRes = cr.continuousCompounding(value, num_periods);

    std::cout<<"Future value for multiple period compounding is "<< res <<std::endl;
    std::cout<<"Future value for continuous compounding is "<<contRes<<std::endl;

    return 0;
}