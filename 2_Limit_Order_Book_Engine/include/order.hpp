#pragma once
#include <cstdint>

using OrderID = uint64_t;
using Price   = int64_t;
using Qty     = int32_t;

enum class Side : uint8_t{
    Buy,
    Sell
};

struct Order{
    OrderID id;
    Side    side;
    Price   price;
    Qty     qty;

    Order* prev = nullptr;
    Order* next = nullptr;
};


