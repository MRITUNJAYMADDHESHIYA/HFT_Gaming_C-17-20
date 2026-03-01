#include "orderbook.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

int Order::order_count_bid = 0;
int Order::order_count_ask = 0;

void OrderBook::flipBalance(const std::string& userId1, const std::string& userId2, double quantity, double price) {
    // Implement the logic to flip balances between two users
    // This function should update the balances of userId1 and userId2 based on the quantity and price of the matched order

    if(users.find(userId1) != users.end() && users.find(userId2) != users.end()) {
        if(users[userId1].user_balance.balance["USD"] >= price * quantity){
            if(users[userId2].user_balance.balance[ticker] >= quantity){
                users[userId1].user_balance.balance["USD"] -= price * quantity;
                users[userId2].user_balance.balance["USD"] += price * quantity;

                users[userId1].user_balance.balance[ticker] += quantity;
                users[userId2].user_balance.balance[ticker] -= quantity;

                cout << "Funds and stocks transfered! " << endl;
            } else {
                cout << "User does not have enough balance to sell the stock " << endl;
            }
        }else{
            cout<<"User does not have enough balance to buy the stock " << endl;
        }
    }else{
        cout<<"One or both users do not exist in the system." << endl;
    }
}


std::string OrderBook::makeUser(std::string Username){
    User user(Username); //create a user with default balance
    users[Username] = user; //add user to the users map
    cout<<"User: " <<Username<<" created successfully "<<endl;
    return "User created successfully";
}




// Users can place bids (add_bid) and asks (add_ask) to the order book.
// The order book matches bids and asks based on price and quantity.
// Balances are adjusted using the flipBalance function.
std::string OrderBook::add_bid(std::string Username, int Price, int Quantity){
    //we need to check if the username exists in the user array,then we compare the value of the bid with the lowest ask price, 
    //if bid >= ask then we start flipping balances and traversing through ask array and bid quantity till condition is false, then if remQty > 0
    int remQty = Quantity;

    //sort asks in ascending order of price and insertion order
    std::stable_sort(asks.begin(), asks.end(), [](const Order &a, const Order &b){
        if(a.price == b.price){
            return a.insert_order_ask < b.insert_order_ask; //if prices are equal, sort by insertion order((first-come, first-served for same price).)
        }
        //otherwise, sort by price
        return a.price < b.price;
    });

    //check if user exists in ask array
    for(auto it=asks.begin(); it != asks.end();){ //no iterator (You might erase elements from the container (like a vector or list) during iteration.)
        if(remQty > 0 && Price >= it->price){
            if(it->quantity > remQty){
                it->quantity -= remQty; //reduce the quantity of the ask order
                flipBalance(Username, it->user_name, remQty, it->price); //
                cout<<"Bid Satisfied successfully at price: "<<it->price <<" and quantity: "<<remQty<<endl;
                remQty = 0; //all quantity satisfied
                break;
            }else{
                remQty -= it->quantity; //reduce the remaining quantity
                flipBalance(Username, it->user_name, it->quantity, it->price);
                cout<<"Bid Satisfied Partially at price: "<<it->price<<" and quantity: "<<it->quantity<<endl;
                it = asks.erase(it); //remove the ask order from the order book
            }
        }else{
            ++it; //move to the next ask order
        }
    }

    //if there is quantity remain then, we add the remaining quantity to the bids order book
    if(remQty > 0){
        Order bid(Username, "bid", Price, remQty);
        bids.push_back(bid); //add the bid order to the order book
        cout<<"Remaining quantity of bids added to Order Book: "<<endl;
    }

    if(remQty == 0){
        cout<<"Complete Bid Satisfied Successfully"<<endl;
    }

    return "Bid added/satisfied successfully. ";       
}



std::string OrderBook::add_ask(std::string Username, int Price, int Quantity){
    int remQty = Quantity;

    std::stable_sort(bids.begin(), bids.end(), [](const Order &a, const Order &b){
        if(a.price == b.price){
            return a.insert_order_bid < b.insert_order_bid; 
        }
        return a.price > b.price; 
    });
    for(auto it=bids.begin(); it != bids.end();){
        if(remQty > 0 && Price <= it->price){
            if(it->quantity > remQty){
                it->quantity -= remQty; 
                flipBalance(Username, it->user_name, remQty, it->price);
                cout<<"Ask Satisfied successfully at price: "<<it->price <<" and quantity: "<<remQty<<endl;
                remQty = 0; 
                break;
            }else{
                remQty -= it->quantity; 
                flipBalance(Username, it->user_name, it->quantity, it->price);
                cout<<"Ask Satisfied Partially at price: "<<it->price<<" and quantity: "<<it->quantity<<endl;
                it = bids.erase(it); 
            }
        }else{
            ++it; 
        }
    }

    if(remQty > 0){
        Order ask(Username, "ask", Price, remQty);
        asks.push_back(ask); 
        cout<<"Remaining quantity of asks added to Order Book: "<<endl;
    }
    if(remQty == 0){
        cout<<"Complete Ask Satisfied Successfully"<<endl;
    }
    return "Ask added/satisfied successfully. ";
}


//Balance of a user
std::string OrderBook::getBalance(std::string username){
    if(users.find(username) != users.end()){
        cout<<"Use found: "<<endl;
        cout<<"User balance is as follows: "<<endl;

        for(const auto& balance : users[username].user_balance.balance){
            cout<<balance.first << ": " << balance.second << endl;
        }
        return "Balance retrieved successfully.";
    }else{
        cout<<"User not found."<<endl;
        return "User not found.";
    }
}


//We will need to find lowest ask prices till the qty passed in is met we keep displaying lowest ask prices
std::string OrderBook::getQuote(int qty){
    std::stable_sort(asks.begin(), asks.end(), [](const Order &a, const Order &b){
        if(a.price == b.price){
            return a.insert_order_ask < b.insert_order_ask;
        }
        return a.price < b.price; 
    });

    for(auto it=asks.begin(); it != asks.end(); ++it){
        if(qty > 0 && qty <= it->quantity){
            cout<<ticker<<"->"<<"Quantity available: " << qty << " at " <<it->price <<" USD"<<endl;
            return "Quote retrieved successfully.";
        }else if(qty > 0 && qty > it->quantity){
            cout<<ticker<<"->"<<"Quantity available: " << it->quantity << " at " <<it->price <<" USD"<<endl;
            qty -= it->quantity; //reduce the quantity
        }else{
            cout<<"Quote retrieved successfully."<<endl;
        }
    }
    cout<<"No more asks available."<<endl;
    return "No more asks available.";
}


//best bid and ask prices and quantities
std::string OrderBook::getDepth(){
    std::sort(asks.begin(), asks.end(), [](const Order &a, const Order &b){
        return a.price > b.price; }); //decreasing order
    std::sort(bids.begin(), bids.end(), [](const Order &a, const Order &b){
        return a.price > b.price; });
    
    //construction
    std::string depthString = ticker + " Depth:\n";

    for(const auto &ask: asks){
        depthString += "\x1b[31m"; // Red color for asks
        depthString += "Price: " + std::to_string(ask.price) + ", Quantity: " + std::to_string(ask.quantity) + "\n";
        depthString += "\x1b[0m"; // Reset color to default
    }
    depthString += "Asks above:\n";
    depthString += "Bids below:\n";
    for(const auto &bid: bids){
        depthString += "\x1b[32m"; // Green color for bids
        depthString += "Price: " + std::to_string(bid.price) + ", Quantity: " + std::to_string(bid.quantity) + "\n";
        depthString += "\x1b[0m"; // Reset color to default
    }

    cout<<depthString<<endl;
    return depthString;
}

std::string OrderBook::addBalanance(std::string Username, std::string market, int value){
    if(users.find(Username) != users.end()){
        users[Username].user_balance.addBalance(market, value);
        cout<<"Balance added successfully for user: " << Username << endl;
        return "Balance added successfully.";
    }
    cout<<"User not found."<<endl;
    return "User not found.";
}


OrderBook::~OrderBook(){
    // Destructor to clean up resources if needed
    //if i want to clear the order book, i can do it here

    // bids.clear();
    // asks.clear();
    // users.clear();
    // cout << "OrderBook destroyed." << endl;
}

void OrderBook::cancelAsk(std::string Username, int Price, int Quantity){
    for(auto it=asks.begin(); it!=asks.end(); ++it){
        if(it->user_name == Username && it->price == Price && it->quantity == Quantity){
            asks.erase(it);
            cout<<"Ask order cancelled successfully."<<endl;
            return;
        }else if(it->user_name == Username && it->price == Price && it->quantity > Quantity){
            it->quantity -= Quantity; //reduce the quantity of the ask order
            cout<<"Ask order quantity reduced successfully."<<endl;
            return;
        }else if(it->user_name == Username && it->price == Price && it->quantity < Quantity){
            cout<<"Ask order quantity is less than the requested quantity."<<endl;
            cout<<"please try again with a smaller quantity."<<endl;
            return;
        }
    }
}

void OrderBook::cancelBid(std::string Username, int Price, int Quantity){
    for(auto it=bids.begin(); it!=bids.end(); ++it){
        if(it->user_name == Username && it->price == Price && it->quantity == Quantity){
            bids.erase(it);
            cout<<"Bid order cancelled successfully."<<endl;
            return;
        }else if(it->user_name == Username && it->price == Price && it->quantity > Quantity){
            it->quantity -= Quantity; //reduce the quantity of the bid order
            cout<<"Bid order quantity reduced successfully."<<endl;
            return;
        }else if(it->user_name == Username && it->price == Price && it->quantity < Quantity){
            cout<<"Bid order quantity is less than the requested quantity."<<endl;
            cout<<"please try again with a smaller quantity."<<endl;
            return;
        }
    }
}

OrderBook::OrderBook() {
    // Implementation of OrderBook constructor

    // Creating a couple of market maker users with predefined balances and bids/asks
    Balances balance1("USD", 10000);
    balance1.addBalance(ticker, 1000);
    User marketMaker1("MarketMaker1", balance1); // User is made
    users["MarketMaker1"] = marketMaker1;        // Adding bids and asks for market makers

    Order bid1("MarketMaker1", "bid", 110, 10);
    Order ask1("MarketMaker1", "ask", 115, 5);
    Order bid2("MarketMaker2", "bid", 111, 8);
    Order ask2("MarketMaker2", "ask", 119, 12);

    bids.push_back(bid1);
    asks.push_back(ask1);
    bids.push_back(bid2);
    asks.push_back(ask2);

    // Creating a couple of market maker users with predefined balances and bids/asks, with different balances to start maintaining liquidity in the order book
    Balances balance2("USD", 10000);
    balance2.addBalance(ticker, 2000);
    User marketMaker2("MarketMaker2", balance2); // User is made
    users["MarketMaker2"] = marketMaker2;        // Adding bids and asks for market makers
    Order bid3("MarketMaker2", "bid", 109, 10);
    Order ask3("MarketMaker2", "ask", 125, 5);
    Order bid4("MarketMaker2", "bid", 112, 8);
    Order ask4("MarketMaker2", "ask", 120, 12);

    bids.push_back(bid3);
    asks.push_back(ask3);
    bids.push_back(bid4);
    asks.push_back(ask4);

    // Creating user 3 with predefined balances and bids/asks
    // market maker 3 has a lot of USD and wants to buy GOOGL
    Balances balance3("USD", 50000);
    balance3.addBalance(ticker, 0);
    User marketMaker3("MarketMaker3", balance3); // User is made
    users["MarketMaker3"] = marketMaker3;        // Adding bids and asks for market makers
    Order bid5("MarketMaker3", "bid", 105, 10);
    Order bid6("MarketMaker3", "bid", 108, 10);
    bids.push_back(bid5);
    bids.push_back(bid6);
}


int main(){
    OrderBook exchange;
    std::string market;
    int choice;
    std::string username;
    int price, quantity;

    cout << "\n=========== " <<"WELCOME TO THE " << ticker << " MARKET "  << "AND HAPPY TRADING" << " =========== \n\n" << endl;
    cout << "\n=========== " << "CURRENT MARKET PRICES " << " =========== " << endl;
    exchange.getDepth(); // getDepth() is called to display the current market

    while(true){
        cout << "\n=========== " << ticker << " Trading Platform ===========\n\n";
        cout << "\n========== Trading Platform Menu ==========\n";
        cout << "1. Sign Up User\n";
        cout << "2. Add Balance to User Account\n";
        cout << "3. Check Current Market Prices\n";
        cout << "4. Add Bid to " << ticker << " v USD market\n";
        cout << "5. Sell your stocks in " << ticker << " v USD Market\n";
        cout << "6. Get Current Quote to buy " << ticker << " stocks\n";
        cout << "7. Check your current User Balance\n";
        cout << "8. Cancel Bid\n";
        cout << "9. Cancel Ask\n";
        cout << "10. Exit\n\n";
        cout << "Enter your choice: ";

        std::cin >> choice;

        switch(choice){
            case 1:
                std::cout<<"Enter username for new user: \n";
                std::cin>>username;
                exchange.makeUser(username);
                break;
            case 2:
                std::cout<<"Enter username for new user: \n";
                std::cin>>username;
                std::cout<<"Enter market(e.g., USD): \n";
                std::cin>>market;
                std::cout<<"Enter balance value: \n";
                int value;
                std::cin>>value;
                exchange.addBalanance(username, market, value);
                break;
            case 3:
                exchange.getDepth();
                break;
            case 4:
                std::cout << "Enter username for bid: \n";
            std::cin >> username;
            std::cout << "Enter bid price: \n";
            std::cin >> price;
            std::cout << "Enter bid quantity: \n";
            std::cin >> quantity;
            exchange.add_bid(username, price, quantity);
            break;
        case 5:
            std::cout << "Enter username for ask: \n";
            std::cin >> username;
            std::cout << "Enter ask price: \n";
            std::cin >> price;
            std::cout << "Enter ask quantity: \n";
            std::cin >> quantity;
            exchange.add_ask(username, price, quantity);
            break;
        case 6:
            std::cout << "Enter quantity for quote: \n";
            std::cin >> quantity;
            exchange.getQuote(quantity);
            break;
        case 7:
            std::cout << "Enter username to get balance: \n";
            std::cin >> username;
            exchange.getBalance(username);
            break;
        case 8:
            std::cout << "Enter username to cancel bid: \n";
            std::cin >> username;
            std::cout << "Enter bid price: \n";
            std::cin >> price;
            std::cout << "Enter bid quantity: \n";
            std::cin >> quantity;
            exchange.cancelBid(username, price, quantity);
            break;
        case 9:
            std::cout << "Enter username to cancel ask: \n";
            std::cin >> username;
            std::cout << "Enter ask price: \n";
            std::cin >> price;
            std::cout << "Enter ask quantity: \n";
            std::cin >> quantity;
            exchange.cancelAsk(username, price, quantity);
            break;
        case 10:
            std::cout << "Exiting the trading platform. Goodbye!\n\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n\n";
        }
    }

    return 0;
}