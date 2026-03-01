#pragma once

#include "Types.h"

struct ExchangeRules{
    Price      tickSize    = 1;       //minimum price increment(in cents)
    Quantity   lotSize     = 1;       //minimun quantity increment(1 share)
    Quantity   minQuantity = 1;       //minimun order size
    Quantity   maxQuantity = 100000;  //max order size
    Price      minNotional = 0;       //minimum order value(price*quantity)-Total value of a trade

    bool IsValidPrice(Price price) const{
        if(price <= 0) return false;
        return price % tickSize == 0;
    }

    bool IsValidQuantity(Quantity quantity) const{
        if(quantity < minQuantity || quantity > maxQuantity) return false;
        return quantity % lotSize == 0;
    }

    //using static_cast<int64_t>
    //Avoid floating-point precision issues (important in finance).
    //Perform fast integer comparisons instead of floating-point.
    bool IsValidNotional(Price price, Quantity quantity) const{
        int64_t notional = static_cast<int64_t>(price)*static_cast<int64_t>(quantity);
        return notional >= minNotional;
    }

    bool IsValidOrder(Price price, Quantity quantity) const {
        return IsValidPrice(price) && IsValidQuantity(quantity) && IsValidNotional(price, quantity);
    }

    //nearest valid tick
    Price RoundToTick(Price price) const {
        if(tickSize <= 1) return price;
        return (price/tickSize) * tickSize;
    }

    //nearest valid lot
    Quantity RoundToLot(Quantity quantity) cosnt{
        if(lotSize <= 1) return quantity;
        return (quantity/lotSize)*lotSize;
    }
};


enum class RejectReason{
    None,
    InvalidPrice,
    InvalidQuantity,
    BelowMinQuantity,
    AboveMaxQuantity,
    BelowMinNotional,
    DuplicateOrderId,
    InvalidOrderType,
    EmptyBook
};


//hold order validation result
struct OrderValidation{
    bool isValid = true;
    RejectReason reason = RejectReason::None;

    static OrderValidation Accept(){
        return OrderValidation{true, RejectReason::None};
    }

    static OrderValidation Reject(RejectReason reason){
        return OrderValidation{false, reason};
    }
};













