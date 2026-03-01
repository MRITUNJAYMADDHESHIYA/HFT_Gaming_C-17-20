
//The implementation file contains the member function ClearingHouse::getClear
// ingHouse. This function first checks the static variable s_clearingHouse to determine if 
// it has been previously allocated. If the object doesn’t exist, then the static function can 
// create a new object, store it for further use, and return a reference.

#include "DesignPatterns.hpp"

ClearingHouse *ClearingHouse::s_clearingHouse = nullptr;
ClearingHouse::ClearingHouse() //private constructor can not be used by client
{}
ClearingHouse::~ClearingHouse()
{}


ClearingHouse &ClearingHouse::getClearingHouse(){
    if(!s_clearingHouse){
        s_clearingHouse = new ClearingHouse();
    }
    return *s_clearingHouse;
}

void ClearingHouse::clearTrade(const Trade &t){
    //Trade is processe here
}

void useClearingHouse(){
    Trade trade;
    ClearingHouse &ch = ClearingHouse::getClearingHouse();
    ch.clearTrade(trade);
}