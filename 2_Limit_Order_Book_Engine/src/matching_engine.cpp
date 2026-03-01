#include "matching_engine.hpp"
#include <iostream>
#include <algorithm>

void MatchingEngine::process(Order* order){
    if(order->side == Side::Buy){
        match_buy(order);
    }else{
        match_sell(order);
    }
}

void MatchingEngine::match_buy(Order* incoming){
    while(incoming->qty > 0){
        PriceLevel* bestAsk = book.best_ask_level();
        if(!bestAsk) break;
        if(bestAsk->price > incoming->price) break;

        Order* resting = bestAsk->head;

        while(resting && incoming->qty > 0){
            Qty trade_qty = std::min(incoming->qty, resting->qty);

            incoming->qty -= trade_qty;
            resting->qty  -= trade_qty;
            bestAsk->total_qty -= trade_qty;

            trade(incoming->id, resting->id, trade_qty, bestAsk->price);

            if(resting->qty == 0){
                Order* to_remove = resting;
                resting = resting->next;
                book.remove_order(to_remove);
            }
        }
    }
    if(incoming->qty > 0){
        book.add_order(incoming);
    }
}

void MatchingEngine::match_sell(Order* incoming) {
    while (incoming->qty > 0) {

        PriceLevel* bestBid = book.best_bid_level();
        if (!bestBid) break;
        if (bestBid->price < incoming->price) break;

        Order* resting = bestBid->head;

        while (resting && incoming->qty > 0) {
            Qty trade_qty = std::min(incoming->qty, resting->qty);

            incoming->qty -= trade_qty;
            resting->qty -= trade_qty;
            bestBid->total_qty -= trade_qty;

            trade(incoming->id, resting->id, trade_qty, bestBid->price);

            if (resting->qty == 0) {
                Order* to_remove = resting;
                resting = resting->next;
                book.remove_order(to_remove);
            }
        }
    }

    if (incoming->qty > 0)
        book.add_order(incoming);
}


void MatchingEngine::trade(OrderID taker, OrderID maker, Qty qty, Price price){
    std::cout << "Trade executed: Taker " << taker << ", Maker " << maker
              << ", Qty " << qty << ", Price " << price << std::endl;   
}