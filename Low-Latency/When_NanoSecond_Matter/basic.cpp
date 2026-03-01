//For OrderBook we have to choose->hash table ( map->logn)

#include<bits/stdc++.h>
using namespace std;

//lets
//AddOrder(OrderOd{1}, Side:Buy, Price{92}, Volume{25});
//AddOrder(OrderOd{2}, Side:Sell, Price{110}, Volume{200});
//ModifyOrder(OrderId{1}, Volume{15});
//DeleteOrder(OrderId{2});

std::map<Price, volume, std::greater<Price>> mBidLevels;
std::map<Price, volume, std::less<Price>> mAskLevels;

template<class T>
typename T::iterator AddOrder(T& levels, Price price, Volume volume){
    auto [it, insert] = levels.try_emplace(price, volume);
    if(inserted == false){
        it->second += volume;
    }
    return it;
}

template<class T>
void DeleteOrder(typename T::iterator it, T& levels, Price price, Volume volume){
    it->second -= volume;
    if(it->second <= 0){
        levels.erase(it);
    }
}