//1.The Singleton pattern ensures that a class has only one instance and provides a global point of access to that instance.
//

#include<iostream>
using namespace std;

class Singleton{
    public:
        Singleton(){
            cout<<"Singleton Constructor called. New Object created."<<endl;
        }
};

int main(){
    Singleton* s1 = new Singleton();
    Singleton* s2 = new Singleton();

    cout<< (s1 == s2 ? "Same Instance" : "Different Instances") <<endl;
    return 0;
}

// /////////////////// 1.Basic Singleton Pattern ///////////////////
// class Singleton{
//     private:
//         static Singleton* instance;
//         Singleton(){} //private constructor to prevent instantiation
//     public:
//         //public static method to access the singleton instance
//         static Singleton* getInstance(){
//             if(instance == nullptr){
//                 instance = new Singleton();
//             }
//             return instance;
//         }

//         void showMessage(){
//             std::cout<<"Singleton instance accessed!"<<std::endl;
//         }
// };

// Singleton* Singleton::instance = nullptr; //initialize static member


// int main(){
//     Singleton* s1 = Singleton::getInstance();
//     s1->showMessage();
//     return 0;
// }