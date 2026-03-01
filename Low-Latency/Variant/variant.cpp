//1.No base class and virtual function
//2.Compile-time type safety
//3.std::visit automatically calls the correct handle

/////Trading order
#include<iostream>
#include<variant>
#include<string>
using namespace std;

struct MarketOrder{
    string symbol;
    double quantity;
};

struct LimitOrder{
    string symbol;
    double quantity;
    double price;
};

struct StopOrder{
    string symbol;
    double quantity;
    double stopPrice;
};

///variant hold any type
using Order = variant<MarketOrder, LimitOrder, StopOrder>;

////std::visit and process it
void processOrder(const Order& order){
    visit([](auto&& ord){
        using T = decay_t<decltype(ord)>;

        if constexpr (is_same_v<T, MarketOrder>){
            cout<<"Executing Market Order for "<< ord.quantity << " units of " <<ord.symbol << endl;
        }else if constexpr(is_same_v<T, LimitOrder>){
            cout<<"Placing Limit Order: "<< ord.quantity << " "<< ord.symbol << "at price "<< ord.price <<endl;
        }else if constexpr(is_same_v<T, StopOrder>){
            cout<<"Setting Stop Order for "<< ord.quantity << " "<< ord.symbol << " with stop price "<< ord.stopPrice <<endl;
        }
    }, order);
}


int main(){
    MarketOrder mo{"XAUUSD", 1.5};
    LimitOrder  lo{"AAPL", 10, 180.50};
    StopOrder   so{"BTCUSD", 0.25, 55000.00};

    Order o1 = mo;
    Order o2 = lo;
    Order o3 = so;

    processOrder(o1);
    processOrder(o2);
    processOrder(o3);

    return 0;
}