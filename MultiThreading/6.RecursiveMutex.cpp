//same thread lock same mutex-lock again but it's not possible so, recursive Mutex introduce
//recursive mutex count how many time lock for unlock also
//




#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor){
    if(loopFor < 0) return;

    m1.lock(); //t1 lock first and t2 wait for unlock this mutex
    cout<<c<<" "<<buffer++<<endl;
    recursion(c, --loopFor);
    m1.unlock();
    cout<<"unlock by thread "<<c<<endl;
}

int main(){
    thread t1(recursion, '1', 10);
    thread t2(recursion, '2', 10);

    t1.join();
    t2.join();
    return 0;
}
