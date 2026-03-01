//1.Notify other thread  ->notify_one() or notify_all()
//2.waiting for some condition


#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money){
    std::lock_guard<mutex> lg(m);
    balance += money;
    cout<< "Amount added current balance: "<<balance<<endl;
    cv.notify_one();
}

void withdrowMoney(int money){
    std::unique_lock<mutex> ul(m);
    cv.wait(ul, []{return (balance != 0) ?true : false;});
    if(balance >= money){
        balance -= money;
        cout<<"Amount Deducted: "<<money<<endl;
    }else{
        cout<<"Amount Can't Be Deducted, Current Balance is less then "<<money<<endl;
    }
    cout<<"Current Balance is: "<<balance<<endl;
}

int main(){
    std::thread t1(withdrowMoney, 500);
    std::thread t2(addMoney, 500);
    t1.join();
    t2.join();

    return 0;
}

//1.let t1 start first
//first lock the mutex
//then cv.wait unlock the ul mutex and wait for notify

//if cv is false then it will wait for notify 
//then t2 will unlockthe lg mutex and then cv.notify_one() working then
//goes at cv.wait and then check for fasle or true 
//if true then it will lock the ul mutex and then check for balance
//or false then repeat the process