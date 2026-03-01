//1.one object only
//Singleton:-Create a private Constructor
//         :-Create a static instace(getInstance) that return the same instance every time.


//Real world:-
//a.Logging system
//b.DataBase connection
//c.Configuration Manager

#include<iostream>
#include<mutex>
using namespace std;

///////////////// Basic Singleton failed //////////
class Singleton{
    public:
        Singleton(){
            cout<<"Singleton Constructor called. New Object created."<<endl;
        }
};

int main(){
    Singleton* s1 = new Singleton();
    Singleton* s2 = new Singleton();

    cout<< (s1 == s2) <<endl;

    return 0;
}

///////////we need to call only once
//////But problem is two getInstance call at same time in thread so, mutex is the solution
class Singleton{
    private:
        static Singleton* instance;

        Singleton(){
            cout<<"Singleton Constructor called. New Object created."<<endl;
        }
    public:
        static Singleton* getInstance(){            
            if(instance == nullptr){
                instance = new Singleton();
            }
            return instance;
        }
};

Singleton* Singleton::instance = nullptr;


///////////////locking is expensive so, as much you can minimize to use is usefull
//////////////solution:-Don't use everytime
class Singleton{
    private:
        static Singleton* instance;
        static mutex mtx;

        Singleton(){
            cout<<"Singleton Constructor called. New Object created."<<endl;
        }
    public:
        static Singleton* getInstance(){
            lock_guard<mutex> lock(mtx); //lock for thread safety
            
            if(instance == nullptr){
                instance = new Singleton();
            }
            return instance;
        }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout<<(s1 == s2)<<endl;

    return 0;
}

//thread save making
//why double locking use:- Because First time let suppose two thread enter
class Singleton{
    private:
        static Singleton* instance;
        static mutex mtx;

        Singleton(){
            cout<<"Singleton Constructor called. New Object created."<<endl;
        }
    public:
        static Singleton* getInstance(){
            if(instance == nullptr){
                lock_guard<mutex> lock(mtx);
                if(instance == nullptr){
                    instance = new Singleton();
                }
            }
            return instance;
        }
};


//////////Eager Initialization
///advantage:-initialize before use
//disadvantage:- if not in use then, memory is already taken

class Singleton{
    private:
        static Singleton* instance;

        Singleton(){
            cout<<"Singleton Constructor Called! "<<endl;
        }

    public:
        static Singleton* getInstance(){
            return instance;
        }
};

Singleton* Singleton::instance = new Singleton();

int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout<<(s1 == s2)<<endl;
}
