//2. Build a Thread-safe bounded queue

//Question:- Implement a bounded blocking queue using condition variables and mutexes. 
//The queue should support multiple produccres and consumers. Ensure there are no deadlocks,
//missed wakeups, or spurious wakeup bugs.

//solution:-
// Multiple producres can push
// Multiple consumers can pop
// Fixed capacity
// if queue is full-->producers block
// if queue is empty--> consumer block
// thread-safe
// no busy waiting



//std::mutex mtx; ---> protects queue data
//std::condition_variable notFull; ----> used by producers
//std::condition_variable notEmpty;----> used by consumers
//always use predicate waits
//wait() -->releases mutex ---- sleeps ----- reacquires mutex
//unlock() before notify to reduce contention

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template<typename T>
class BoundedQueue{
    private:
        std::queue<T> q_;
        const std::size_t capacity_;

        std::mutex mtx_;
        std::condition_variable notFull_;
        std::condition_variable notEmpty_;

    public:
        explicit BoundedQueue(std::size_t capacity) : capacity_(capacity) {}

        void push(const T& value){
            std::unique_lock<std::mutex> lock(mtx_);

            //wait for free space till producer sleep
            notFull_.wait(lock, [this]{
                return q_.size() < capacity_;
            });

            q_.push(value);
            lock.unlock();
            notEmpty_.notify_one();
        }

        T pop(){
            std::unique_lock<std::mutex> lock(mtx_);

            //queue empty consumer sleeps
            notEmpty_.wait(lock, [this]{
                return !q_.empty();
            });

            T value = q_.front();
            q_.pop();

            lock.unlock();
            notFull_.notify_one();

            return value;
        }
};


//// Learning:-
//1.Explicit ---> 
//if a constructor can be called with a single argument, the C++ compiler treats it as a converting constructor. This means the compiler will automatically (implicitly) convert data of the argument's type into your class type behind the scenes

//2.condition_variable --->
//a synchronization primitive used to block one or more threads until another thread modifies a shared variable (the condition) and notifies the waiting thread(s)


//3.Deadlock is impossible
//only one mutex + no lock ordering problems
//deadlock needs--->thread A waiting for thread B  + thread B waiting for thread A

//4.mutex ---->
// It ensures that only one thread can execute a critical section of code at a given time.
// While you can lock and unlock a mutex manually using mtx.lock() and mtx.unlock()

//5.std::unique_lock --->
// It automatically locks a mutex upon creation and unlocks it when it falls out of scope, guaranteeing exception safety and avoiding deadlocks.
//


