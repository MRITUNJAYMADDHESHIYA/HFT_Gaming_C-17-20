#include "investment.h"
#include "intRateEngine.h"

#include <iostream>

int main(){
    IntRate<Bond> engineA;
    IntRate<Mortgage> engineB;

    Bond bond(40000, 250);
    Mortgage mor(250, 50000, 5000);
    engineA.setInstrument(bond);
    engineB.setInstrument(mor);

    std::cout<< "bond annual int rate: "<< engineA.getAnnualIntRate()*100 << "%" <<std::endl;
    std::cout<< "mortgage annual int rate: "<<engineB.getAnnualIntRate()*100 <<"%" <<std::endl;

    return 0;
}