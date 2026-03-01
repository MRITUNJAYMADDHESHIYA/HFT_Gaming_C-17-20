#pragma once

#include<vector>
#include "Types.h"

struct LevelInfo{
    Price    price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>

class OrderbookLevelInfos{
    public:
        OrderbookLevelInfos(const LevelInfos &bids, const LevelInfos &asks): bids_{bids}, asks{asks}{}

        const LevelInfo &GetBids() const{return bids_;}
        const LevelInfo &GetAsks() const{return asks_;}

    private:
        LevelInfos bids_;
        LevelInfos asks_;
};
