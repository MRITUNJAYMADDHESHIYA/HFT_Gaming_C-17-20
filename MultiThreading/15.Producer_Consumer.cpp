//Ask in interview
 
//a producer and a consumer, that share a bounded buffer. The producer generates data and adds it to the buffer, while the consumer retrieves and processes that data. The core issue is ensuring that the producer doesn't try to add data to a full buffer and the consumer doesn't try to remove data from an empty buffer. 

//producer took the lock -> produce the data ->notify the consumer but you have to release the mutex
//consumer notify to producer i am done
//this cycle keep going untill producer does not have any data



//////////////***********///////////////////
// THE PROBLEM STATEMENT:
//  1. Producer will produce and consumer will consume with synchronisation of a common buffer.
//  2. Until producer thread produces any data consumer thread can't consume.
//  3. Threads will use condition_variable to notify each other.
//  4. We need mutex if we use condition_variable because CV waits on mutex.
//  5. This is one of the example of producer consumer there are many.

// PRODUCER thread steps:
//  1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
//  2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
//  3. insert item in buffer.
//  4. unlock mutex. 
//  5. notify consumer.

// CONSUMER thread steps:
//  1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
//  2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume.
//  3. consume item from buffer.
//  4. unlock mutex.
//  5. notify producer.

#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>
using namespace std;

std::mutex mu;
std::condition_variable cond_val;
deque<int> buffer;
const unsigned int maxBufferSize = 50;

void producer(int val){
    while(val){
        std::unique_lock<std::mutex> locker(mu); //aquire the lock first
        cond_val.wait(locker, [](){return buffer.size() < maxBufferSize;}); //if full then wait

        buffer.push_back(val);
        cout<< "Produced: "<<val<<endl;
        val--;
        locker.unlock();
        cond_val.notify_one();
    }
}

void consumer(){
    while(true){
        std::unique_lock<std::mutex> locker(mu);
        cond_val.wait(locker, [](){return buffer.size() > 0}); //atleast 1 data
        
        int val = buffer.back(); //remove it from buffer
        buffer.pop_back();
        cout<<"Consumed: "<<val<<endl;
        locker.unlock();
        cond_val.notify_one();
    }
}

int main(){
    std::thread t1(producer, 100);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}