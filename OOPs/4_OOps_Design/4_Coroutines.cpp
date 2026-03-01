//1.cotoutines make async code cleaner and non-blocking without extra thread


#include<iostream>
#include<coroutine>
#include<thread>
#include<chrono>

struct Task{
    struct promise_type{
        Task get_return_object(){return {};}
        std::suspend_never initial_suspend() {return {};}
        std::suspend_never final_suspend() noexcept {return {};}
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task asyncPrint(){
    std::cout<< "starting async work... \n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"work done!\n";
    co_return;
}

int main(){
    asyncPrint();
    std::cout<<"Main thread countinues...\n";
}
