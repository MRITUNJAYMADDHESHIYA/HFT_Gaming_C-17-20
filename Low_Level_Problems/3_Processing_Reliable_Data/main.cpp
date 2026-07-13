//Problem:-
//In high-performance systems, processing data fast is important, but processing reliable data is even more critical.


// Imagine a trading system receiving data from two different lines:
// Primary line---> The main source of incoming market data
// Secondary line --> A backup line running continuously in parallel
 
// Normal conditions, the consumer should process data coming from primary line.
// But the real challenge starts when the primary feed begins sending bad or inconsistent data.
// due to (packet corruption, stale messages, sequence gaps)

//Solution:------
//keep listening to both primary and secondary feeds continuously
//validate every incoming packet from the primary feed
//process primary feed as long as the data remains healthy
//immediately switch to the seccondary feed the moment bad data is detected
//continue monitoring the primary feed in the background
//automatically switch back once the primary feed becomes stable again


#include<iostream>
#include<thread>
#include<atomic>

enum class FeedType{
    PRIMARY,
    SECONDARY
};


class MarketDataFeedHandler{
    std::atomic<FeedType> activeFeed;
    std::atomic<int>      primaryData{0};
    std::atomic<int>      secondaryData{0};
    std::atoic<bool>      running{true};

    public:
        bool validatePrimaryFeed(int value){
            return value % 5 != 0;
        }

        void primaryLine(){
            int value = 0;
            while(running){
                std::cout << "Data received over the primary Line:\t" <<value <<std::endl;
                if(validatePrimaryFeed(value)){
                    primaryData = value;
                }else{
                    activeFeed = FeedType::SECONDARY;
                    std::cout<<"Error: bad data over the primaryLine, switching to secondary" << std::endl;
                }
                value++;
                std::this_thread::sleep_for(1s);
            }
        }

        void secondaryLine(){
            int value = 100;
            while(running){
                secondaryData = value;
                value++;
                std::this_thread::sleep_for(1s);
            }
        }

        void dataConsumer(){
            int value = 100;
            while(running){
                if(activeFeed==FeedType::PRIMARY){
                    std::cout<< "Consuming from the primary line, data=" << primaryData <<std::endl;
                }else{
                    std::cout<<"Consuming form the secondary line, data=" <<secondaryData <<std::endl;
                    activeFeed = FeedType::PRIMARY;
                }
                std::this_thread::sleep_for(1s);
            }
        }

        void stop(){
            running = false;
        }
};

int main(){
    MarketDataFeedHandler system;
    std::thread t1(&MarketDataFeedHandler::primaryLine, &system);
    std::thread t2(&MarketDataFeedHandler::secondaryLine, &system);
    std::thread t3(&MarketDataFeedHandler::dataConsumer, &system);
    std::this_thread::sleep_for(30s);
    system.stop();
    t1.join();
    t2.join();
    t3.join();
    return 0;
}









//Learning:-
//1.enum class----->
//                  No implicity converts enum to integer and namespace pollution
//                  better type safety

enum class Side : uint16_t{
    BUY,
    SELL
};
enum class orderType : uint16_t{
    MARKET,
    LIMIT
};


//2.atomic ----> allows multiple threads to safely access and modify a shared variable without a data race.
//Protect a single variable


//3.mutex ---->
//protect a critical section
//
