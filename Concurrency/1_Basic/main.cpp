//1.What is concurrency and multithreading?
//Concurrency is about two or more separate activities happening at the same time.

//Two approaches to Concurrency:- parallel execution on a dual-core machine
//                             :- Task switching on a single-core machine

//Concurrency with multiple processes
//Concurrency with multiple thread

//Concurrency:- I can handle many tasks at once
//multithreading:- I have many hands(threads) in the same body(process)
//multithreading is one technique to achieve concurrency.


#include<iostream>
#include<thread>

void hello(){
    std::cout<<"Hello Concurrent World\n";
}

int main(){
    std::thread t(hello);
    t.join();
}

