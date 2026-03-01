#pragma once
#include "order.hpp"
#include <map>
#include <unordered_map>
#include <vector>
#include <cstdint>

static constexpr Price MAX_PRICE = 200000;
static constexpr size_t BITMAP_SIZE = (MAX_PRICE / 64) + 1;

struct PriceLevel{
    Price price;
    Qty   total_qty = 0;
    Order* head     = nullptr;   //oldest order
    Order* tail     = nullptr;   //newest order
};


// ////////////// using vector ///////////
// class OrderBook{
//     public:
//         OrderBook();

//         void add_order(Order* order);
//         void remove_order(Order* order);
//         void cancel_order(OrderID id);

//         PriceLevel* best_bid_level();
//         PriceLevel* best_ask_level();

//         Price best_bid() const {return best_bid_price; }
//         Price best_ask() const {return best_ask_price; }

//     private:
//         std::vector<PriceLevel> bids;
//         std::vector<PriceLevel> asks;

//         std::unordered_map<OrderID, Order*> order_map;
        
//         Price best_bid_price = 0;
//         Price best_ask_price = MAX_PRICE;

//         void add_to_level(PriceLevel& level, Order* order);
//         void remove_from_level(PriceLevel& level, Order* order);

//         void update_best_bid(Price price);
//         void update_best_ask(Price price);
// };


//////////// using map ////////////////
class OrderBook{
    public:
        void add_order(Order* order);
        void cancel_order(OrderID id);
        void remove_order(Order* order);

        Price best_bid() const;
        Price best_ask() const;

        PriceLevel* best_bid_level();
        PriceLevel* best_ask_level();

        void print_book() const;
    
    private:
        std::map<Price, PriceLevel, std::greater<Price>> bids; //highest price first
        std::map<Price, PriceLevel, std::less<Price>> asks;
        std::unordered_map<OrderID, Order*> order_map;

        void add_to_level(PriceLevel& level, Order* order);
        void remove_from_level(PriceLevel& level, Order* order);
};