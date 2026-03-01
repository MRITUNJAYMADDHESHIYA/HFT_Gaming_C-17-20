#include<iostream>

class Demo{
    public:
        int x;
        void show(){ //show(const Demo* this)
            std::cout << this->x << std::endl; //this is pointing current object
        }
};
int main(){
    Demo d1{10};
    d1.show(); //== Demo::show(&d1); 
}