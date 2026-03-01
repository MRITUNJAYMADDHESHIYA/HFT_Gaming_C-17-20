#include "order_book.hpp"
#include <iostream>

//OrderBook::OrderBook() : bids(MAX_PRICE + 1), asks(MAX_PRICE+1) {}


//fifo + o(1) insertion/deletion + quantity tracking
void OrderBook::add_to_level(PriceLevel& level, Order* order){

    //new order added at the tail
    order->prev = level.tail; //prev points to old tail
    order->next = nullptr;    //next is null as it's the newest order

    if(level.tail){
        level.tail->next = order;
    }else{
        level.head = order;
    }

    level.tail = order;
    level.total_qty += order->qty;
}

void OrderBook::remove_from_level(PriceLevel& level, Order* order){
    if(order->prev){
        order->prev->next = order->next;
    }else{
        level.head = order->next;
    }

    if(order->next){
        order->next->prev = order->prev;
    }else{
        level.tail = order->prev;
    }

    level.total_qty -= order->qty;

    order->prev = nullptr;
    order->next = nullptr;
}


void OrderBook::add_order(Order* order) {

    if (order->side == Side::Buy) {
        auto& level = bids[order->price];
        add_to_level(level, order);
    } else {
        auto& level = asks[order->price];
        add_to_level(level, order);
    }

    order_map[order->id] = order;
}

void OrderBook::remove_order(Order* order)
{
    if (!order) return;
    if (order->side == Side::Buy){
        auto it = bids.find(order->price);
        if (it == bids.end()) return;

        remove_from_level(it->second, order);

        if (it->second.head == nullptr)
            bids.erase(it);
    }
    else{
        auto it = asks.find(order->price);
        if (it == asks.end()) return;

        remove_from_level(it->second, order);

        if (it->second.head == nullptr)
            asks.erase(it);
    }

    order_map.erase(order->id);
}

void OrderBook::cancel_order(OrderID id){
    auto it = order_map.find(id);
    if(it == order_map.end()) return;

    remove_order(it->second);
}

Price OrderBook::best_bid() const{
    if(bids.empty()) return 0;
    return bids.begin()->first;
}

Price OrderBook::best_ask() const{
    if(asks.empty()) return 0;
    return asks.begin()->first;
}

PriceLevel* OrderBook::best_bid_level(){
    if(bids.empty()) return nullptr;
    return &bids.begin()->second;
}

PriceLevel* OrderBook::best_ask_level(){
    if(asks.empty()) return nullptr;
    return &asks.begin()->second;
}


void OrderBook::print_book() const{
    std::cout<< "\n---ORDER BOOK---\n";

    std::cout<< "Asks:\n";
    for(auto& [p, level_it] : asks){
        std::cout<< "Price: " << p << " Total Qty: " << level_it.total_qty << "\n";
    }

    std::cout<< "Bids:\n";
    for(auto& [p, level_it] : bids){
        std::cout<< "Price: " << p << " Total Qty: " << level_it.total_qty << "\n";
    }
}
