#include "fundamental.h"
#include <iostream>

int main(int argc, const char* argv[]){
    Fundamental fc("APPL", 543.334, 12.2);

    fc.setAssets(243139);
    fc.setBookValue(165234);
    fc.setEarnings(35885);
    fc.setEpsGrowth(0.22);
    fc.setExpectedEarnings(39435);
    fc.setLiabilitiesAndIntangibles(124642);
    fc.setNetIncome(37235);
    fc.setNumOfShare(891990);
    fc.setShareHoldersEquity(123549);
    std::cout << "P/E: " << fc.PE()/1000 << std::endl; // prices in thousands
    std::cout << "forward P/E: " << fc.forwardPE()/1000 << std::endl;
    std::cout << "book value: " << fc.bookValue() << std::endl;
    std::cout << "price to book: " << fc.priceToBookRatio() << std::endl;
    std::cout << "price earnings to growth: " << fc.
    priceEarningsToGrowth() << std::endl;
    std::cout << "return on equity: " << fc.returnOnEquity() << std::endl;
    std::cout << "dividend: " << fc.getDividend() << std::endl;
    return 0;
}