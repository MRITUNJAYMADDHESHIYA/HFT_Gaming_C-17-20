#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include<string>
#include<vector>
#include<unordered_map>

std::string ticker = "TESL"; //data

//struct using for simple code over class
struct Balances{
    std::unordered_map<std::string, int> balance; //{usd, tesla value}
    Balances(){
        balance["USD"]  = 0;
        balance[ticker] = 0;
    }

    Balances(std::string market, int value){
        balance[market] = value;
    }

    std::string addBalance(std:: string market, int value){
        // if balance array contains the market, add the value to the balance
        if(balance.find(market) != balance.end()){
            balance[market] += value;
            return "Balance added successfully";
        }
        balance[market] = value;
        return "Balance added successfully";
    }
};



//stores unique user name and balances for each user
struct User{
    std::string user_name;
    Balances user_balance;

    User(){};

    User(std::string Username, Balances b){
        user_name    = Username;
        user_balance = b;
    }

    User(std::string Username){
        user_name    = Username;
        user_balance = Balances(); //default balance is 1000 USD and 0 TESLA
    }
};


//user can place an order to buy/sell a certain quantity of a stock at a certain price, and this order is stored in the order book or is matched and balances are exchanged
struct Order{
    std::string user_name;
    std::string side;
    int price;
    int quantity;
    static int order_count_bid; //using one shared memory(because of static)
    static int order_count_ask;
    int insert_order_bid;       //order in which the order was inserted into the order book
    int insert_order_ask;

    Order(std::string Username, std::string Side, int Price, int Quantity){
        user_name = Username;
        side      = Side;
        price     = Price;
        quantity  = Quantity;
        if(side == "bid"){
            insert_order_bid = order_count_bid++;
        }else{
            insert_order_ask = order_count_ask++;
        }
    }
};



class OrderBook{
    private:
        std::vector<Order> bids;
        std::vector<Order> asks;
        std::unordered_map<std::string, User> users; //This is complex for me
        void flipBalance(const std::string& userId1, const std::string& userId2, double quantity, double price);

    public:
        OrderBook();
        ~OrderBook();
        std::string add_bid(std::string Username, int Price, int Quantity);  //adds a bid or ask to the order book
        std::string add_ask(std::string Username, int Price, int Quantity);
        std::string getBalance(std::string username); //returns the balance of a user
        std::string getQuote(int qty); //returns the best bid and ask prices and quantities
        std::string getDepth();        // returns the best bid and ask prices and quantities
        std::string makeUser(std::string); // creates a new user for people trying to join the market
        std::string addBalanance(std::string Username, std::string market, int value); // adds balance to a user
        void cancelBid(std::string Username, int Price, int Quantity); // cancels a bid or ask from the order book
        void cancelAsk(std::string Username, int Price, int Quantity);
};

#endif 
