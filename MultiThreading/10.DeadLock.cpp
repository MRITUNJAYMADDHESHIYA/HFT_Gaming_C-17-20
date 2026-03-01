#include<iostream>
#include<thread>
#include<mutex> 
using namespace std;

std::mutex m1;
std::mutex m2;  


//only problem is both threads are trying to lock the mutexes in different order
//let thread1 lock m1 and thread2 lock m2  --> deadlock occurs

void thread1(){
    m1.lock();
    m2.lock();
    cout<<"Thread 1 is running"<<endl;
    m1.unlock();
    m2.unlock();
}

void thread2(){
    m2.lock();
    m1.lock();
    cout<<"Thread 2 is running"<<endl;
    m2.unlock();
    m1.unlock();
}

int main(){
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}