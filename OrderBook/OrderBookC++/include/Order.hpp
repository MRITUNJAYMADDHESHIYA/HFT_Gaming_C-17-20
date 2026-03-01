#pragma once

#include<cstdint>
#include "Enums.hpp"
#include "Helper.hpp"

struct Order{
    int quantity;
    BookSide side;
    double price;
    uint64_t timestamp;

    //constructor
    //time when order is created
    Order(int q, doubel p, BookSide s, uint64_t t=unix_time()): quantity{q}, price{p}, side{s}, timestamp{t} {}
};