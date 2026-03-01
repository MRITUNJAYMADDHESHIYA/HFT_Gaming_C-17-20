// Producer-Consumer problem.
// Sleeping Barber Problem.
// Dining Philosopher’s Problem.
// Readers and Writers Problem.



//////using mutex and condition_variable method
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <semaphore.h>
using namespace std;

queue<int> buffer;
const unsigned int maxSize = 5;
mutex mtx;
condition_variable cv;

void producer() {
    int item = 0;
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < maxSize; });

        buffer.push(item++);
        cout << "Produced: " << item << endl;

        lock.unlock();
        cv.notify_all();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        lock.unlock();
        cv.notify_all();
        this_thread::sleep_for(chrono::milliseconds(800));
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}



// //////////////////////////////using semaphore
// //Using std::binary_semaphore in MinGW-w64 under Windows is unreliable as of now.
// //i can use the mutex method for this
// std::binary_semaphore signal_to_producer{1},
// std::binary_semaphore signal_to_consumer{0};

// #define buff_size 5
// int buff[buff_size];

// void producer(){
//     while(1){
//         signal_to_producer.acquire(); //first acquire beacuse of 1
//         cout<<"Producer = ";
//         for(int i=0; i<buff_size; i++){
//             buff[i] = i*i;
//             cout<< buff[i] <<" "<<std::flush;
//             std::this_thread::sleep_for(std::chrono::milliseconds(200));
//         }
//         cout<<endl;
//         signal_to_consumer.release();
//     }
// }

// void consumer(){
//     while(1){
//         signal_to_consumer.acquire();
//         cout<<"Consumed = ";
//         for(int i=buff_size-1; i>=0; i--){
//             cout<<buff[i]<<" "<<std::flush;
//             buff[i]=0;
//             std::this_thread::sleep_for(std::chrono::milliseconds(200));
//         }
//         cout<<endl; cout<<endl;
//         signal_to_producer.release();
//     }
// }

// int main(){
//     std::thread producer_thread(producer);
//     std::thread consumer_thread(consumer);

//     std::cout<<"[main] Got the signal\n";
//     producer_thread.join();
//     consumer_thread.join();

//     return 0;
// }