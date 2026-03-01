#include "bond.h"
#include<iostream>

int main(int argc, const char* argv[]){
    if(argc != 4){
        std::cout<< "usage: progName <institution> <principle> <coupon> <num periods>" << std::endl;
        return 1;
    }

    std::string issu = argv[1];
    double principle = atof(argv[2]);
    double coupon    = atof(argv[3]);
    int num_periods  = atoi(argv[4]);

    Bond bc(issu, principle, coupon, num_periods);
    std::cout<<" reasing information for bond issued by " << issu <<std::endl;
    std::cout<<" the internal rate of return is "<< bc.interestRate()<<std::endl;
    return 0;
}

