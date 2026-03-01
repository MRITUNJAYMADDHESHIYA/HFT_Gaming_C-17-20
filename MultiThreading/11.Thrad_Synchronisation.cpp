//thread or process synchronization
//1.Thread Or Process Synchronization to access critical section
//2.Critical section is one or collection of program statements which should be excuted by only one thread or process at a time

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

long long bankBalance = 0;
void addMoney(long long val){
    m.lock(); //lock the mutex
    bankBalance += val;
    m.unlock(); //unlock the mutex
}

//here critical section is bankBalance
//if two threads try to add money at the same time then it will lead
//solution is to use mutex
std::mutex m;
int main(){
    std::thread t1(addMoney, 1000);
    std::thread t2(addMoney, 2000);

    t1.join();
    t2.join();

    cout<<"Bank Balance: "<<bankBalance<<endl;
    return 0;
}