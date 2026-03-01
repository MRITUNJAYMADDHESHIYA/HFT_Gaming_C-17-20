//std::scoped_lock is a RAII-style (Resource Acquisition Is Initialization) synchronization utility introduced in C++17. It's used to acquire one or more mutexes simultaneously and release them automatically when the scoped_lock object goes out of scope.

#include<iostream>
#include<thread>
#include<mutex>

std::mutex m1;
std::mutex m2;

void processData(int id){
    std::scoped_lock lock(m1, m2);
    std::cout<<"Thread "<<id<<":Processing data with m1 and m2"<<std::endl;
}

int main(){
    const int numThread = 3;
    std::thread threads[numThread];

    for(int i=0; i<numThread; ++i){
        threads[i] = std::thread(processData, i);
    }

    for(int i=0; i<numThread;++i){
        threads[i].join();
    }
    return 0;
}