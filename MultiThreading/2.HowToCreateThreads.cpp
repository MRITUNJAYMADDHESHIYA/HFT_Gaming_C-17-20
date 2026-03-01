//There is 5 different type we can create thread in c++11

//Note:->If we create multiple threads at the same time it doesn't guarantee which one will start first.

#include<iostream>
#include<thread>
using namespace std;
// //1.Function Pointer
// void fun(int x){
//     while(x-- > 0){
//         cout<<x<<endl;
//     }
// }

// int main(){
//     std::thread t1(fun, 11);
//     t1.join();
//     return 0;
// }


// //2.Lambda Function
// int main(){
//     auto fun = [](int x){
//         while(x-- > 0){
//             cout<<x<<endl;
//         }
//     };

//     std::thread t(fun, 10);
//     t.join();
//     return 0;
// }

// //3.Funtor(Function object)
// class Base{
//     public:
//         void operator()(int x){
//             while(x-- > 0){
//                 cout<<x<<endl;
//             }
//         }
// };
// int main(){
//     std::thread t(Base(), 10);
//     t.join();
//     return 0;
// }

//4.Non-static member function
// class Base{
//     public:
//         void run(int x){
//             while(x-- > 0){
//                 cout<<x<<endl;
//             }
//         }
// };
// int main(){
//     Base b;
//     std::thread t(&Base::run, &b, 10);
//     t.join();
//     return 0;
// }

////5. Static memebar function
////You don't need any object
class Base{
    public:
        static void run(int x){
            while(x-- > 0){
                cout<<x<<endl;
            }
        }
};
int main(){
    std::thread t(&Base::run, 10);
    t.join();
    return 0;
}