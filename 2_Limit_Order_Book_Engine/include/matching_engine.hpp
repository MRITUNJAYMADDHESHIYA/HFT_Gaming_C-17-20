#pragma once
#include "order_book.hpp"

class MatchingEngine{
    public:
        void process(Order* order);
    private:
        OrderBook book;

        void match_buy(Order* order);
        void match_sell(Order* order);

        void trade(OrderID taker, OrderID maker, Qty qty, Price price);
};
