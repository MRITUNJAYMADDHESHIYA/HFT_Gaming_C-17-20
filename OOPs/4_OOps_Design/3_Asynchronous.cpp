//It’s a class function that does its work in the background, while your main program keeps running.

//live data
//execute order placement
#include<iostream>
#include<future>
#include<thread>
#include<chrono>

class MarketData{
    public:
        int fetchPrice(){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 2500;
        }
        

        std::future<int> fetchPriceAsync(){
            return std::async(std::launch::async, &MarketData::fetchPrice, this);
        }
};

int main(){
    MarketData md;

    std::cout<<"Request Price data ..\n";

    std::future<int> pricefuture = md.fetchPriceAsync();

    std::cout<<"Doing other work: \n";

    int price = pricefuture.get();
    std::cout<<"Fetched price: "<< price <<"\n";

    return 0;
}