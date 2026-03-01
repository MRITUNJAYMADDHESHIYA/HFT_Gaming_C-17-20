//is static variable thread safe or not ->NO

//different output
#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

static int s = 0;
void fun(){
    int count = 100000;
    while(count--){
        ++s;
    }
    cout<< s <<" "<<endl;
}

int main(){
    std::thread t1(fun);
    std::thread t2(fun);
    t1.join();
    t2.join();

    return 0;
}