//single producer single consumer
//Producer: writes data into buffer, then updates tail with release.
//Consumer: loads tail with acquire, ensuring it sees the buffer contents.

//consumer pop-->head only moves forward
//producer push-->tail only moves forward

// relaxed → no ordering guarantees, just atomicity.
// acquire → ensure all later reads/writes happen after this load.
// release → ensure all earlier writes happen before this store.

//producer side
// buffer[t] = item;                 // (1) write data
// tail.store(next, release);        // (2) publish new tail

//consumer side
// size_t t = tail.load(acquire);    // (A) read producer’s tail safely
// item = buffer[h];                 // (B) guaranteed to see data from (1)


#include<iostream>
#include<atomic>
#include<thread>
#include<vector>
#include<chrono>
#include<optional>

template<typename T>
class SPSCQueue{
    std::vector<T> buffer;
    const size_t  capacity;
    std::atomic<size_t> head{0}, tail{0};

    public:
        explicit SPSCQueue(size_t cap): buffer(cap), capacity(cap){} //constructor

        bool push(const T& item){
            size_t t = tail.load(std::memory_order_relaxed);
            size_t h = head.load(std::memory_order_acquire);

            size_t next = (t+1)%capacity;
            if(next == h) return false; //queue full

            buffer[t] = item;
            tail.store(next, std::memory_order_release);
            return true;
        }

        std::optional<T> pop(){
            size_t h = head.load(std::memory_order_relaxed);
            size_t t = tail.load(std::memory_order_acquire);

            if(h == t){
                return std::nullopt; //queue empty
            }

            T item = buffer[h];
            head.store((h+1)%capacity, std::memory_order_release);
            return item;
        }
};


//////////////////////////////////Market Data//////////////////////////
struct MarketTick{
    int price;
    int quantity;
};

///////////////////////////////////Main////////////////////////////////
int main(){
    SPSCQueue<MarketTick> q(8);  //buffer of size 8


    //Producer thread
    std::thread producer([&](){
        int price = 100;
        for(int i=0; i<20; i++){
            MarketTick tick{price++, 10+i};

            while(!q.push(tick)){
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
            std::cout<<"[Producer] sent tick: price="<<tick.price<<" qty="<<tick.quantity<<"\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    //consumer thread
    std::thread consumer([&](){
        for(int i=0; i<20; i++){
            std::optional<MarketTick> tick;
            while(!(tick = q.pop())){
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
            std::cout<<" [Consumer] Got Tick: Price="<<tick->price<<" qty="<<tick->quantity<<"\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
    });


    producer.join();
    consumer.join();
    return 0;
}