#include "matching_engine.hpp"
#include<iostream>

int main(){
    MatchingEngine engine;
    Order s1{1, Side::Sell, 100, 5};
    Order s2{2, Side::Sell, 100, 5};

    Order b1{3, Side::Buy, 100, 8};

    engine.process(&s1);
    engine.process(&s2);
    engine.process(&b1);

    return 0;
}

//g++ *.cpp -I../include -o main
//main