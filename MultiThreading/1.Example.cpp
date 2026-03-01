//1.main() function is the only thread when no other threads are created.
//2. Threads is also know as lightweight process. (like a process, but with less overhead and try to parallelization of tasks)

//eg:-browser multiple tabs, each tab is a thread.
//  :-spell checking in text editor, each word is a thread.
//  :-vs code, auto completing the code to give me different options







//Find the sum of all odd number from 1 to 1,900,000,000 and even number from 1 to 1,900,000,000 using multithreading.
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end){
    for(ull i=start; i<=end; i++){
        if((i&1) == 0){
            evenSum += i;
        }
    }
}

void findOdd(ull start, ull end){
    for(ull i=start; i<=end; i++){
        if((i&1) == 1){
            OddSum += i;
        }
    }
}


int main(){
    ull start = 0, end = 1900000000;

    auto startTime = high_resolution_clock::now();

    std::thread t1(findEven, start, end);
    std::thread t2(findOdd, start, end);
    t1.join();
    t2.join();
    // findOdd(start, end);
    // findEven(start, end);

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime-startTime);

    cout<< "OddSum:"<<OddSum<<endl;
    cout<< "EvenSum:"<<evenSum<<endl;

    cout<<"Sec:" <<duration.count()/1000000<<endl;
    return 0;
}