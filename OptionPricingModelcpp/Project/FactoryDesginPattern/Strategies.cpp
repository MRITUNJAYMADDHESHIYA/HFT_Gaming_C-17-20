//different type of strategy
#include<iostream>
#include<unordered_map>

enum StrategyType{
    Aggressive,
    Passive
};


//When a function is declared virtual in a base class, it tells the compiler that this function can be overridden in any derived class.
class Strategy{
    public:
        int order_qty;
        double price;
        virtual void CreateStrategy(const int order_qty, const double price) = 0;
        virtual ~Strategy(){
            std::cout<<"Strategy class destructor called" << std::endl;
        }
};

class AggressiveStrategy: public Strategy{
    public:
        void CreateStrategy(const int order_qty, const double price){
            this->order_qty = order_qty;
            this->price     = price;
            std::cout<<"Aggressive strategy created, order_qty:"<<this->order_qty <<",price" << this->price<<std::endl;
        }
        ~AggressiveStrategy(){
            std::cout<<"Aggressive destructor called"<<std::endl;
        }
};

class PassiveStratey: public Strategy{
    public:
        void CreateStrategy(const int order_qty, const double price){
            this->order_qty = order_qty;
            this->price     = price;
            std::cout<<"Passive strategy created, oreder_qty:"<<this->order_qty<<" ,price"<<this->price<<std::endl;
        }
        ~PassiveStratey(){
            std::cout<<"PassiveStrategy destructor called"<< std::endl;
        }
};

class StrategyFactory{
    std::unordered_map<StrategyType, Strategy*> strategies;
    public:
        StrategyFactory(){
            BuildStrategyFactory();
        }
        ~StrategyFactory(){
            std::cout<<"destructor called"<<std::endl;

            delete strategies[StrategyType::Aggressive];
            delete strategies[StrategyType::Passive];
        }

        Strategy* GetStrategy(const StrategyType type){
            switch(type){
                case StrategyType::Aggressive:
                    return strategies[StrategyType::Aggressive];
                case StrategyType::Passive:
                    return strategies[StrategyType::Passive];
                default:
                    return strategies[StrategyType::Aggressive];
            }
        }

    private:
        void BuildStrategyFactory(){
            Strategy* s1 = new AggressiveStrategy();
            Strategy* s2 = new PassiveStratey();
            strategies[StrategyType::Aggressive] = s1;
            strategies[StrategyType::Passive]    = s2;
        }
};