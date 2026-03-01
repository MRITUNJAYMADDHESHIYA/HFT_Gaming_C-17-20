//defer_lock   -> do not acquire ownership of the mutex
//try_to_lock  -> try to acquire ownership of the mutex without blocking.
//adopt_lock   -> assume the calling thread already has ownership of the mutex.


#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

std::mutex m1;
int buffer = 0;

void task(const char* threadNumber, int loopFor){
    std::unique_lock<mutex> lock(m1); //automatically calls lock on m1
    // m1.lock();
    for(int i=0; i<loopFor; i++){
        buffer++;
        cout<< threadNumber << buffer <<endl;
    }
    // m1.unlock();
}


void task2(const char* threadNumber, int loopFor){
    std::unique_lock<mutex> lock(m1, std::defer_lock); //automatically calls lock on m1
    lock.lock();
    for(int i=0; i<loopFor; i++){
        buffer++;
        cout<< threadNumber << buffer <<endl;
    }
}

int main(){
    thread t1(task, "T1", 10);
    thread t2(task, "T2", 10);
    t1.join();
    t1.join();
    return 0;
}

