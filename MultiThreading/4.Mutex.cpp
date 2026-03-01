#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

// //Mutex: Mutual Exclusion
// //Mutex is used to avoid the race condition
// //we use lock(), unlock() on mutex to avoid  race condition

// //Race condition:->
// //1.racc condition is a situation where two or more tread happend to change a common data at the same time.

// int myAmount = 0;
// std::mutex m;

// void addMoney(){
//     m.lock();
//     ++myAmount;
//     m.unlock();
// }


// int main(){
//     std::thread t1(addMoney);
//     std::thread t2(addMoney);

//     t1.join();
//     t2.join();

//     cout<<myAmount<<endl;
//     return 0;
// }

// //////mutex::try_lock()
// //1.Try to lock the mutex.return immediately
// //2.

// int counter=0;
// std::mutex mtx;

// void increaseTheCounter(){
//     for(int i=0; i<100000; i++){
//         if(mtx.try_lock()){
//             ++counter;
//             mtx.unlock();
//         }
//     }
// }

// int main(){
//     std::thread t1(increaseTheCounter);
//     std::thread t2(increaseTheCounter);

//     t1.join();
//     t2.join();

//     cout<< "counter" <<counter<<endl;
//     return 0;
// }


///std::try_lock() in c++
///it can try to lock multiple mutex objects at the same time

int X = 0, Y = 0;
std::mutex m1, m2;
void doSomeWorkForSeconds(int seconds){std::this_thread::sleep_for(std::chrono::seconds(seconds));}

void incrementXY(int &XorY, std::mutex& m, const char* desc){
    for(int i=0; i<5; i++){
        m.lock();
        ++XorY;
        std::cout << desc << XorY << std::endl;
        m.unlock();
        doSomeWorkForSeconds(1);
    }
}

void consumeXY(){
    int useCount = 5;
    int XplusY = 0;
    while(1){
        int lockResult = std::try_lock(m1, m2);
        if(lockResult == -1){
            if(X!=0 && Y!=0){
                useCount--;
                XplusY += X+Y;
                X=0;
                Y=0;
                cout<<"XplusY: " << XplusY << endl;
            }
            m1.unlock();
            m2.unlock();
            if(useCount == 0) break;
        }
    }
}
int main(){
    std::thread t1(incrementXY, std::ref(X), std::ref(m1), "X ");
    std::thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y ");
    std::thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}