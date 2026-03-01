//1.Pre-condition and 2.post-condition
#include<iostream>
#include<vector>
#include<stdexcept>

//a precondition must be statisfied before a method can be executed
//sub classes can weaken the precondition but cannot streanthen it.
class User{
    public:
        virtual void setPassword(string password){
            if(password.length() < 8){
                throw invalid_argument("Password must be at least 8 character long!");
            }
            std::cout<<"Password set succesfully"<<std::endl;
        }
};

class AdminUser : public User{
    public:
        //precondition: password must be at least 6 character
        void setPassword(string password) override {
            if(password.length() < 6){
                throw invalid_argument("Password must be at least 6 character long!");
            }
            std::cout<<"Password set successfully"<<std::endl;
        }
};

///A postcondition must be statisfied after a method is executed
//sub classes can strengthen the postcondition but cannot weaken it.

class Car{
    protected:
        int speed;
    public:
        Car(){
            speed = 0;
        }

        void accelerate(){
            std::cout<< "Accelerating"<<std::endl;
            speed += 20;
        }

        //postcondition
        virtual void brake(){
            std::cout<<"Applying brakes"<<std::endl;
            speed -= 10;
        }
};

class HybridCar : public Car{
    private:    
        int charge;
    public:
        HybridCar() : Car() {charge = 0;}

        //postcondition: speed must reduce after brake
        //postcondition: charge must increase
        void brake(){
            std::cout<<"Applying brakes"<<std::endl;
            speed -= 10;
            charge += 10;
        }
};