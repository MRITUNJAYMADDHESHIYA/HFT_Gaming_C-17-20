#include "cashFlow.h"
#include<iostream>

int main(int argc, const char* argv[]){
    if(argc != 2){
        std::cout<<" usage: progName <interest rate> " <<std::endl;
        return 1;
    }

    double rate = atof(argv[1]);
    CashFlow cf(rate);
    do{
        int period;
        std::cin >> period;
        if(period == -1){
            break;
        }
        double value;
        std::cin>>value;
        cf.addCashPayment(value, period);
    }while(1);

    double result = cf.presentValue();
    std::cout<<"The present value is " << result << std::endl;

    return 0;
}

//g++ main.cpp cashFlow.cpp -o main
//main 0.08
//1 200
//2 300
//3 500
//4 -1000
//-1