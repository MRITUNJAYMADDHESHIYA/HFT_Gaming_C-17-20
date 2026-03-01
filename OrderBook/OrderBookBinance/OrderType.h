#pragma once

enum class OrderType{
    GoodTillCancel,      //active until completely filled
    ImmediateOrCancel,   //fill for as far as possible and kill immediatly
    Market,              //fill at any price
    GoodForDay,          //all of these are cancelled at a specific time every day
    FillOrKill           //fill fully or kill immediately
};

enum class Side{
    Buy,
    Sell
};