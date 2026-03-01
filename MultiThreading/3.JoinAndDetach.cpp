// //join()->wait for complete the program
// //detach() and joinable() in C++ multithreading


// #include<iostream>
// #include<chrono>
// #include<thread>
// using namespace std;

// // //join
// // void run(int count){
// //     while(count-- >0){
// //         cout<<"TradingMrity"<<endl;
// //     }
// //     std::this_thread::sleep_for(chrono::seconds(5));
// // }

// // int main(){
// //     std::thread t1(run, 10);
// //     cout<<"main()"<<endl;

// //     t1.join();
// //     if(t1.joinable()){ // This will return false as t1 is already joined
// //         t1.join();
// //     }
// //     cout<<"main() after"<<endl;
// //     return 0;
// // }


// //Detach -> more faster than join, basically Lets the thread run independently
// void run(int count){
//     while(count-- >0){
//         cout<<count<<"TradingMrity"<<endl;
//     }
//     cout<< "thread finished" <<endl;
// }

// int main(){
//     std::thread t1(run, 10);
//     cout<<"main()"<<endl;

//     t1.detach();
//     // if(t1.joinable()){
//     //     t1.detach();
//     // }

//     cout<<"main() after"<<endl;
//     //std::this_thread::sleep_for(chrono::seconds(5));
//     return 0;
// }


#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
