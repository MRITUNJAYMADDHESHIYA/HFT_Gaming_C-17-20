#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>

#include "Order.h"
#include "OrderModify.h"
#include "Trade.h"
#include "LevelInfo.h"
#include "Types.h"

class Orderbook{
    private:
        //Store order pointer and its position in the price level list
        struct OrderEntry{
            OrderPointer order_{nullptr};
            OrderPointer::iterator location_; //Iterator to quickly erase from list
        };

        std::map<Price, OrderPointers, std::greater<Price>> bids_;
        std::map<Price, OrderPointers, std::less<Price>> asks_;
        std::unordered_map<OrderId, OrderEntry> orders_;
}