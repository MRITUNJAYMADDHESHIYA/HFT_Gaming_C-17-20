//std::async  ->creating a task
//it automatically creates a thread and a promise object for us


//a.std::launch::async
//b.std::launch::deffered
//c.std::launch::async | std::launch::deffered

#include<iostream>
#include<thread>
#include<future>

using namespace std;
using namespace std::chrono;
typedef long int ull;

ull findOdd(std::promise<ull>&& OddSumPromise, ull start, ull end){
    ull OddSum = 0;
    for(ull i=start; i<=end; ++i){
        if(i&1){
            OddSum += i;
        }
    }
    return OddSum;
}
int main(){
    ull start = 0, end = 1900000000;

    cout<<"Thread created if policy is std::launch::async!!"<<endl;
    std::future<ull> OddSum = std::async(std::launch::deferred, findOdd, start, end);
    cout<<"Waiting For Result!! "<<endl;

    cout<<"OddSum: "<<OddSum.get()<<endl;
    cout<<"Completed!! "<<endl;
    t1.join();
    return 0;
}