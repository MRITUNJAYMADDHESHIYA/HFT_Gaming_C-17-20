//std::weak_ptr:-(It is used in conjunction with shared_ptr to avoid circular references. It does not affect the reference count of the shared_ptr it points to.)

// std::shared_ptr<int> sharedPtr = std::make_shared<int>(30);
// std::weak_ptr<int> weakPtr = sharedPtr; // weakPtr does not affect the reference count of sharedPtr

//unique_ptr is for unique ownership and shared_ptr is for shared ownership then weak_ptr is for non-ownership samrt pointer.
//a weak_ptr is created as a copy of shared_ptr.

// #include<iostream>
// #include<memory>
// using namespace std;

// int main(){
//     auto sharedPtr = std::make_shared<int>(100);
//     std::weak_ptr<int> weakPtr(sharedPtr);

//     std::cout<<"weakPtr.use_count(): "<<weakPtr.use_count()<<std::endl;
//     std::cout<<"sharedPtr.use_count(): "<<sharedPtr.use_count()<<std::endl;
//     std::cout<<"weakPtr.expired(): "<<weakPtr.expired()<<std::endl;

//     if(std::shared_ptr<int> sharedPtr1 = weakPtr.lock()){
//         std::cout<<"*sharedPtr: "<<*sharedPtr<<std::endl;
//         std::cout<<"sharedPtr1.use_count(): "<<sharedPtr1.use_count()<<std::endl;
//     }else{
//         std::cout<<"Don't get the resource! "<<std::endl;
//     }


//     weakPtr.reset();
//     if(std::shared_ptr<int> sharedPtr1 = weakPtr.lock()){
//         std::cout<<"*SharedPtr: "<<*sharedPtr<<std::endl;
//         std::cout<<"SharedPtr1.use_count(): "<<sharedPtr1.use_count()<<std::endl;
//     }else{
//         std::cout<<"Don't get the resource! after reset "<<std::endl;
//     }
//     return 0;
// }


////////////////////////********************////////////////////////
#include<iostream>
#include<memory>

struct Son;
struct Daughter;

struct Mother{
    ~Mother(){
        std::cout<<"Mother gone "<<std::endl;
    }
    void setSon(const std::shared_ptr<Son> s){
        mySon = s;
    }
    void setDaughter(const std::shared_ptr<Daughter> d){
        myDaughter = d;
    }

    std::weak_ptr<Son> mySon; //break the cyclic dependencies
    std::shared_ptr<Daughter> myDaughter;
};

struct Son{
    Son(std::shared_ptr<Mother> m) : myMother(m){}
    ~Son(){
        std::cout<<"Son gone "<<std::endl;
    }
    std::shared_ptr<const Mother> myMother;
};

struct Daughter{
    Daughter(std::shared_ptr<Mother> m) : myMother(m){}
    ~Daughter(){
        std::cout<<"Daughter gone "<<std::endl;
    }
    std::shared_ptr<const Mother> myMother;
};

int main(){
    std::cout<<std::endl;
    {
        std::shared_ptr<Mother> mother = std::shared_ptr<Mother>(new Mother);
        std::shared_ptr<Son>    son    = std::shared_ptr<Son>(new Son(mother));
        std::shared_ptr<Daughter>daughter = std::shared_ptr<Daughter>(new Daughter(mother));
        mother->setSon(son);
        mother->setDaughter(daughter);
    }
    std::cout<<std::endl;
}