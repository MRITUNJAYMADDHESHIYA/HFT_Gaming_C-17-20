#include "Observer.hpp"
using namespace std;

typedef shared_ptr<Observer> PObserver;
typedef shared_ptr<TradeObserver> PTradeObserver;

Observer::Observer(){}
Observer::Observer(const Observer &p){}
Observer::~Observer(){}
void Observer::notify(){}


TradeObserver::TradeObserver(TradingLedger *t):
    m_ledger(t)
{}
TradeObserver::TradeObserver(const TradeObserver &p):
    m_trade(p.m_trade),
    m_ledger(p.m_ledger)
{}
TradeObserver::~TradeObserver()
{}
TradeObserver &TradeObserver::operator=(const TradeObserver &p){
    if(this !=&p){
        m_trade = p.m_trade;
        m_ledger = p.m_ledger;
    }
    return *this;
}

void TradeObserver::notify(){
    this->processNewTrade();
}
void TradeObserver::processNewTrade(){
    m_trade = m_ledger->getLastTrade();
    //Do trading processing here
}



//TradingLedger
TradingLedger::TradingLedger(){}
TradingLedger::TradingLedger(const TradingLedger &p):
    m_observer(p.m_observer),
    m_trade(p.m_trade)
{}
TradingLedger::~TradingLedger()
{}
TradingLedger &TradingLedger::operator=(const TradingLedger &p){
    if(this != &p){
        m_observer = p.m_observer;
        m_trade = p.m_trade;
    }
    return *this;
}

void TradingLedger::addObserver(PObserver observer){
    m_observer.insert(observer);
}
void TradingLedger::removeObserver(PObserver observer){
    if(m_observer.find(observer) != m_observer.end()){
        m_observer.erase(observer);
    }
}
void TradingLedger::triggerNotification(){
    for(auto i:m_observer){
        i->notify();
    }
}
void TradingLedger::addTrde(const Trade &t){
    m_trade = t;
    this->triggerNotification();
}
const Trade &TradingLedger::getLastTrade(){
    return m_trade;
}



int main(){
    TradingLedger t1;
    PTradeObserver Observer1 = PTradeObserver(new TradeObserver(&t1));
    PTradeObserver Observer2 = PTradeObserver(new TradeObserver(&t1));
    t1.addObserver(Observer1);
    t1.addObserver(Observer2);

    //perform trading system
    Trade aTrade;
    t1.addTrde(aTrade);

    return 0;

}
