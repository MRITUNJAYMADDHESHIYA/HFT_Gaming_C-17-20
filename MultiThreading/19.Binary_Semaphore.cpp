#include<iostream>
#include<chrono>
#include<semaphore.h>
#include<thread>


//global binary semaphore instances
//object counts are set to zero
//objects are in non-signaled state
std::binary_semaphore
    smphSignalMainToThread{0},
    smphSignalThreadToMain{0};

void ThreadProc(){

    //wait for a signal from the main proc
    //by attempting to decrement the semaphore
    smphSignalMainToThread.acquire();

    //this call back until the semaphore's count
    //is increased from the main proc
    std::cout<<"[thread] Got the signal\n";

    using namespace std::literals;
    std::this_thread::sleep_for(3s);

    std::cout<< "[thread] send the signal\n";

    //signal the main proc back
    smphSignalThreadToMain.release();
}

int main(){
    std::thread thrWorker(ThreadProc); //create some worker thread
    std::cout<<"[main] Send the signal\n";

    //signal the worker thread to start working
    //by increading the semaphore's count
    smphSignalMainToThread.release();

    //wait until the worker thread is done doing the work
    //by attempting to decrement the semaphore's count
    smphSignalThreadToMain.acquire();

    std::cout<<"[main] Got the signal\n";
    thrWorker.join();


}