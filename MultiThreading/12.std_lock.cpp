//very Important

//it is used to lock multiple mutex at the same time.
//std::lock(m1, m2, m3, m4);
//1.order of locking is not define
//2.No dead Lock situation
#include<iostream>
#include<mutex>
#include<thread>

std::mutex m1, m2;

void task_a(){
    while(1){
        std::lock(m1, m2);
        std::cout << "task a\n";
        m1.unlock();
        m2.unlock();
    }
}

void task_b(){
    while(1){
        std::lock(m2, m1);
        std::cout<<"task b\n";
        m2.unlock();
        m1.unlock();
    }
}

int main(){
    std::thread th1(task_a);
    std::thread th2(task_b);

    th1.join();
    th2.join();
    return 0;
}