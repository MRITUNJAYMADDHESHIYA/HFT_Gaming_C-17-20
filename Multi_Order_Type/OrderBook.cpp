#include<iostream>
#include<vector>
#include<stdexcept>
#include<cstdint>
#include<list>
#include<memory>
#include<format> //for std::format, available in C++20, but we can use it in C++14 with a library like fmtlib   
#include<string>
#include<algorithm>

using namespace std;

enum class OrderType{
    GoodTillCancel,
    FillAndKill,
    FillOrKill,
    GoodForDay,
    Market,
};

enum class Side{
    Buy,
    Sell
};

using Price    = std::int32_t;
using Quantity = std::uint32_t;
using OrderId  = std::uint32_t;

///////////////////////////////////level information
struct LevelInfo{
    Price price_;
    Quantity quantity_;
};
using LevelInfos = std::vector<LevelInfo>;


class OrderbookLevelInfos{
    public:
        OrderbookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
            : bids_{ bids}
            , asks_{ asks } {} //the compiler to directly initialize the member variables bids_ and asks_ with the passed arguments.

        const LevelInfos& GetBids() const { return bids_;} //They return a const reference to avoid copying the entire vector.
        const LevelInfos& GetAsks() const { return asks_;}

    private:
    LevelInfos bids_;
    LevelInfos asks_;
};


////////////////////////////////////Order objects and Quantity
class Order{
    public:
        Order(OrderType orderType, OrderId, orderId, Side side, Price price, Quantity quantity)
            : orderType_{ orderType }
            , orderId_{ orderId }
            , side_{ side }
            , price_{ price }
            , initiaQuantity_{ quantity }
            , reaminingQuantity_{ quantity} {}


        //API to access order details
        OrderId GetOrderId() const {return orderId_;}
        Side GetSide() const { return side_; }
        Price GetPrice() const { return price_; }
        OrderType GetOrderType() const { return orderType_; }
        Quantity GetInitialQuantity() const { return initiaQuantity_; }
        Quantity GetRemainingQuantity() const { return reaminingQuantity_; }
        Quantity GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }
        bool IsFilled() const { return GetRemainingQuantity() == 0; }


        void Fill(Quantity quantity){
            if(quantity > GetRemainingQuantity()){
                throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));
            }
            reaminingQuantity_ -= quantity;
        }

    private:
        OrderType orderType_;
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity initiaQuantity_;
        Quantity reaminingQuantity_;
};

//we store a single order in a multiple data structure in OrderBook
using OrderPointer = std::shared_ptr<Order>; //manages shared ownership of a dynamically allocated object.
using OrderPointers = std::list<OrderPointer>; //a doubly linked list that allows for efficient insertions and deletions.


/////////////////////////////////Modify Order
class OrderModify{
    public:
        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity):
            orderId_{ orderId }
            , side_{ side }
            , price_{ price }
            , quantity_{ quantity } {}
        
        OrderId GetOrderId() const { return orderId_; }
        Side GetSide() const { return side_; }
        Price GetPrice() const { return price_; }
        Quantity GetQuantity() const { return quantity_; }

        OrderPointer ToOrderPointer(OrderType type) const {
            return std::make_shared<Order>(type, GetOrderId(), GetSide(), GetPrice(), GetQuantity());
        }
    private:
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity quantity_;
};


/////////////////////////////////Match Order
struct TradeInfo{
    OrderId orderId_;
    Price price_;
    Quantity quantity_;
};

class Trade{
    public:
        Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade):
            bidTrade_{ bidTrade },
            askTrade_{ askTrade } {}

        const TradeInfo& GetBidTrade() const { return bidTrade_; }
        const TradeInfo& GetAskTrade() const { return askTrade_; }
    
    private:
        TradeInfo bidTrade_;
        TradeInfo askTrade_;   
};

using Trades = std::vector<Trade>; //a vector to store multiple trades.



////////////////////////////////Store Order
class Orderbook{
    private:
        struct OrderEntry{ //Stores pointer to order and its exact position in order list
            OrderPointer order_{nullptr}; //a shared pointer to an Order object
            OrderPointers::iterator location_;//an iterator pointing to the location of the order in the OrderPointers list
        };

        std::map<Price, OrderPointers, std::greater<Price>> bids_;
        std::map<Price, OrderPointers, std::less<Price>> asks_;
        std::unordered_map<OrderId, OrderEntry> orders_;


        bool CanMatch(Side side, Price price) const {
            if(side == Side::Buy){
                if(asks_.empty()) return false;
                const auto&[bestAsk_, _] = *asks_.begin(); //best ask
                return price >= bestAsk_;
            }else{
                if(bids_.empty()) return false; 
                const auto&[bestBid_, _] = *bids_.begin(); //best bid
                return price <= bestBid_;
            }
        }


        /////////////////////Match Order
        Trades MatchOrders(){
            Traders trades;
            trades.reserve(orders_.size()); //reserve space for trades to avoid multiple reallocations

            while(true){
                if(bids_.empty() || asks_.empty()) break;

                auto& [bidPrice, bids] = *bids_.begin();
                auto& [askPrice, asks] = *asks_.begin();

                if(bidPrice < askPrice) break; //no match possible

                while(!bids.empty() && !asks.empty()){
                    auto bidOrder = bids.front();
                    auto askOrder = asks.front();

                    // if(bidOrder->GetRemainingQuantity() == 0){
                    //     bids.pop_front();
                    //     continue;
                    // }
                    // if(askOrder->GetRemainingQuantity() == 0){
                    //     asks.pop_front();
                    //     continue;
                    // }

                    Quantity matchQuantity = std::min(bidOrder->GetRemainingQuantity(), askOrder->GetRemainingQuantity());
                    // TradeInfo bidTrade{bidOrder->GetOrderId(), bidPrice, matchQuantity};
                    // TradeInfo askTrade{askOrder->GetOrderId(), askPrice, matchQuantity};

                    // trades.emplace_back(bidTrade, askTrade);

                    bidOrder->Fill(matchQuantity);
                    askOrder->Fill(matchQuantity);

                    if(bidOrder->IsFilled()){
                        bids.pop_front();
                        orders_.erase(bidOrder->GetOrderId());
                    } 
                    if(askOrder->IsFilled()){
                        asks.pop_front();
                        orders_.erase(askOrder->GetOrderId());
                    }

                    if(bids.empty()) bids_.erase(bidPrice);
                    if(asks.empty()) asks_.erase(askPrice);

                    trades.push_back(Trade{
                        TradeInfo{bidOrder->GetOrderId(), bidOrder->GetPrice(), matchQuantity},
                        TradeInfo{askOrder->GetOrderId(), askOrder->GetPrice(), matchQuantity}
                    });

                    // OnOrderMatched(bidOrder->GetPrice(), matchQuantity, bidOrder->IsFilled());
                    // OnOrderMatched(askOrder->GetPrice(), matchQuantity, askOrder->IsFilled());
                }
                
                if(!bids_.empty()){
                    auto& [_, bids] = *bids_.begin();
                    auto& order = bids.front();
                    if(order->GetOrderType() == OrderType::FillAndKill) CancelOrder(order->GetOrderId());
                }

                if(!asks_.empty()){
                    auto& [_, asks] = *asks_.begin();
                    auto& order = asks.front();
                    if(order->GetOrderType() == OrderType::FillAndKill) CancelOrder(order->GetOrderId());
                }
                return trades;
            }
        }

    public:
        
};















int main(){
    return 0;
}