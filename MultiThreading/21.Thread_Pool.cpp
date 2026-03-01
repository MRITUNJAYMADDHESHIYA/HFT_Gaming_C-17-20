#include<iostream>
#include<vector>
#include<thread>
#include<queue>
#include<functional>

#include<mutex>
#include<condition_variable>
#include<sstream>

class ThreadPool{
    public:
        ThreadPool(size_t numThreads) : stop(false){
            for(size_t i=0; i<numThreads; ++i){
                workers.emplace_back([this]{ //how to push threads in vector
                    //lemda function
                    for(;;){
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] {return stop || !tasks.empty();});
                        
                        if(stop && tasks.empty()) return;

                        auto task = std::move(tasks.front());//excract task from tasks list
                        tasks.pop();
                        lock.unlock();//unlock the mutex, so another thread can accept the tasks
                        task(); //run the task
                    }
                });
            }
        }

        template<class F>
        void enqueue(F&& task){
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::forward<F>(task));
            lock.unlock();
            condition.notify_one();
        }

        ~ThreadPool(){
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
            lock.unlock();
            condition.notify_all();
            for(std::thread& worker: workers){
                worker.join();
            }
        }
    
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks; //pushing function pointer tasks
        std::mutex queueMutex;
        std::condition_variable condition;
        bool stop;
};

std::string get_thread_id(){
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss<< myid;
    std::string mystr = ss.str();
    return mystr;
}

int main(){
    ThreadPool pool(4); //create a pool with n number of worker thread
    std::cout<<"Thread pool created\n";
    std::cout<<"Enqueue assign some task\n";

    for(int i=0; i<8; ++i){
        //lamda function
        pool.enqueue([i] {
            std::cout << "Task " << i << " executed by thread " << get_thread_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }

    //main thread continues doing other things
    //while the tasks are executed in the background

    return 0;
}








////////////There is a topic Object pool
