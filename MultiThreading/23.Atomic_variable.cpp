#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int counter;
int times = 1000;
void run(){
    for(int i=0; i<times; i++){
        ++counter;
    }
}

int main(){
    std::thread m1(run);
    std::thread m2(run);

    m1.join();
    m2.join();

    cout<< counter<<endl;
    return 0;
}