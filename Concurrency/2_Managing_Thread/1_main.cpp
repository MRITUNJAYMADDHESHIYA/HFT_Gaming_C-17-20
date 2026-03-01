//1.Basic thread management
//2.Launching a thread


#include<iostream>
#include<thread>

class background_task{
    public:
        void operator() () const{
            do_something();
            do_something_else();
        }
};

background_task f;
std::thread my_thread(f);

std::thread my_thread(background_task());


