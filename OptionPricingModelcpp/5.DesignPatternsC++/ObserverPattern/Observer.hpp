#ifndef Observer_hpp
#define Observer_hpp

#include<set>
#include<memory> //for shared_ptr
using namespace std;

class Observer{
    public:
        Observer();
        Observer(const Observer &p);
        ~Observer();
        Observer &operator=(const Observer &p);

        virtual void notify()=0;
};

//Implementation not shown here
class Trade{};
class TradingLedger; //forward decleration


//The constructor for this class receives as a parameter a pointer to the TradingLedger 
// object, which will be defined later. The class provides an implementation for 
// notifications and a member function to process new trades.
class TradeObserver : public Observer{
    public:
        TradeObserver(TradingLedger *t);
        TradeObserver(const TradeObserver &p);
        ~TradeObserver();
        TradeObserver &operator=(const TradeObserver &p);

        void notify();
        void processNewTrade();
    private:
        Trade m_trade;
        TradingLedger *m_ledger;
};

class TradingLedger{
    public:
        TradingLedger();
        TradingLedger(const TradingLedger &p);
        ~TradingLedger();
        TradingLedger &operator=(const TradingLedger &p);

        void addObserver(shared_ptr<Observer> Observer);
        void removeObserver(shared_ptr<Observer> Observer);
        void triggerNotification();

        void addTrde(const Trade &t);
        const Trade &getLastTrade();

    private:
    set<shared_ptr<Observer>> m_observer;
    Trade m_trade;
};

#endif