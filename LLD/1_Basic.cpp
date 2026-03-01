//LLD:- (Code structures) Scalable + Maintainable + Reusable
//HLD:- (Tech Stack, Architecture, DB Design, SeverScale, Cost Optimization, ER Diagram, UML Diagrams)
//DSA:- (Time and Space Complexity, Patterns, Problem Solving Approaches)


//OOPs:- Real world modelling using Classes and Objects + data security + reusable + maintaible + scalable

//Abstraction:- Hiding internal details and showing only functionality(data hiding)
//Encapsulation:- Binding data members and member functions together + data security(using access specifiers)
#include<iostream>
using namespace std;

//For Abstraction demo
class Car{
    public:
        virtual void startEngine()       = 0;
        virtual void shiftGear(int gear) = 0;
        virtual void accelerate()        = 0;
        virtual void brake()             = 0;
        virtual void stopEngine()        = 0;
        virtual ~Car() {}
};

class SportCar : public Car{
    public:
        string brand;
        string model;
        bool   isEngineOn;
        int    currentSpeed;
        int    currentGear;

        SportCar(string b, string m){
            this->brand     = b;
            this->model     = m;
            isEngineOn      = false;
            currentSpeed    = 0;
            currentGear     = 0;
        }

        void startEngine(){
            isEngineOn = true;
            cout << brand << " " << model << ": Engine starts with a roar!" << endl;
        }

        void shiftGear(int gear){
            if(!isEngineOn){
                cout << brand <<" " << model <<" : Engine is off! Cannot shift Gear." << endl;
                return;
            }
            currentGear = gear;
            cout << brand << " " << model << ": Shifted to gear " << currentGear << endl;
        }

        void accelerate(){
            if(!isEngineOn){
                cout << brand <<" " << model <<" : Engine is off! Cannot accelerate." << endl;
                return;
            }
            currentSpeed += 20;
            cout << brand << " " << model << ": Accelerating! Current speed: " << currentSpeed << " km/h" << endl;
        }

        void brake(){
            currentSpeed -= 20;
            if(currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << ": Braking! Current speed: " << currentSpeed << " km/h" << endl;
        }

        void stopEngine(){
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0;
            cout << brand << " " << model << ": Engine stopped." << endl;
        }
};


//For Encapsulation demo
class SportCar1{
    private:
        //data members
        string brand;
        string model;
        bool   isEngineOn;
        int    currentSpeed;
        int    currentGear;
        string tyre;

    public:
        SportCar(string b, string m){
            this->brand     = b;
            this->model     = m;
            isEngineOn      = false;
            currentSpeed    = 0;
            currentGear     = 0;
            tyre            = "MRF";
        }

        //getters and setters can be added here for private members if needed
        //if I want to public the private member
        string getTyre(){
            return this->tyre;
        }

        string setTyre(string tyre){
            return this->tyre;
        }

        //data members functions
        void startEngine(){
            isEngineOn = true;
            cout << brand << " " << model << ": Engine starts with a roar!" << endl;
        }

        void shiftGear(int gear){
            if(!isEngineOn){
                cout << brand <<" " << model <<" : Engine is off! Cannot shift Gear." << endl;
                return;
            }
            currentGear = gear;
            cout << brand << " " << model << ": Shifted to gear " << currentGear << endl;
        }

        void accelerate(){
            if(!isEngineOn){
                cout << brand <<" " << model <<" : Engine is off! Cannot accelerate." << endl;
                return;
            }
            currentSpeed += 20;
            cout << brand << " " << model << ": Accelerating! Current speed: " << currentSpeed << " km/h" << endl;
        }

        void brake(){
            currentSpeed -= 20;
            if(currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << ": Braking! Current speed: " << currentSpeed << " km/h" << endl;
        }

        void stopEngine(){
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0;
            cout << brand << " " << model << ": Engine stopped." << endl;
        }
};

int main(){
    Car* myCar = new SportCar("Ferrari", "488 GTB");

    myCar->startEngine();
    myCar->shiftGear(1);
    myCar->accelerate();
    myCar->shiftGear(2);
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine();

    delete myCar;
    return 0;
}


//Polymorphism:- (Compile time + Run time)
//Dynamic Poly :- Method overriding (Inheritance + Virtual Functions) (declare in base class and override in derived class)
//Static  Poly:- Method overloading (Function name same with different parameters) + Operator overloading (+, -, *, / etc)

class Car1{
    private:
        string brand;
        string model;
        bool   isEngineOn;
        int    currentSpeed;

    public:
        SportCar(string b, string m){
            this->brand     = b;
            this->model     = m;
            isEngineOn      = false;
            currentSpeed    = 0;
        }

        void startEngine(){
            isEngineOn = true;
            cout << brand << " " << model << ": Engine starts with a roar!" << endl;
        }

        void stopEngine(){
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0;
            cout << brand << " " << model << ": Engine stopped." << endl;
        }


        virtual void accelerate() = 0; //dynamic polymorphism
        virtual void brake()      = 0; //dynamic polymorphism
        virtual ~Car1() {} 
};

class ManualCar : public Car1{
    private:
        int currentGear;
    public:
        ManualCar(string brand, string model) : Car1(brand, model){
            this->currentGear = 0;
        }

        //Specialized method for Manual Car
        void shiftGear(int gear) {
            currentGear = gear;
            cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
        }

        // Overriding accelerate - Dynamic Polymorphism
        void accelerate() {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            currentSpeed += 20;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
        }

        // Overriding brake - Dynamic Polymorphism
        void brake() {
            currentSpeed -= 20;
            if (currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
        }
};

class ElectricCar : public Car {
    private:
        int batteryLevel;

    public:
        ElectricCar(string brand, string model) : Car(brand, model) {
            this->batteryLevel = 100;
        }

        //specialized method for Electric Car
        void chargeBattery() {
            batteryLevel = 100;
            cout << brand << " " << model << " : Battery fully charged!" << endl;
        }

        // Overriding accelerate - Dynamic Polymorphism
        void accelerate() {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            if (batteryLevel <= 0) {
                cout << brand << " " << model << " : Battery dead! Cannot accelerate." << endl;
                return;
            }
            batteryLevel -= 10;
            currentSpeed += 15;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
        }

        // Overriding brake - Dynamic Polymorphism
        void brake() {
            currentSpeed -= 15;
            if (currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << " : Regenerative braking! Speed is now " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
        }
};

int main() {
    Car* myManualCar = new ManualCar("Suzuki", "WagonR");
    myManualCar->startEngine();
    myManualCar->accelerate();
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();

    cout << "----------------------" << endl;

    Car* myElectricCar = new ElectricCar("Tesla", "Model S");
    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->accelerate();
    myElectricCar->brake();
    myElectricCar->stopEngine();

    // Cleanup
    delete myManualCar;
    delete myElectricCar;

    return 0;
}


//Static Polymorphism demo
class ManualCar {
    private:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;

    public:
        ManualCar(string brand, string model) {
            this->brand = brand;
            this->model = model;
            this->isEngineOn = false;
            this->currentSpeed = 0;
            this->currentGear = 0;
        }

        void startEngine() {
            isEngineOn = true;
            cout << brand << " " << model << " : Engine started." << endl;
        }

        void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            cout << brand << " " << model << " : Engine turned off." << endl;
        }

        // Overloading accelerate - Static Polymorphism
        void accelerate() {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            currentSpeed += 20;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
        }

        void accelerate(int speed) {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            currentSpeed += speed;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
        }

        void brake() {
            currentSpeed -= 20;
            if (currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
        }

        void shiftGear(int gear) {
            currentGear = gear;
            cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
        }
};

int main() {
    ManualCar* myManualCar = new ManualCar("Suzuki", "WagonR");
    myManualCar->startEngine();
    myManualCar->accelerate();
    myManualCar->accelerate(40);
    myManualCar->brake();
    myManualCar->stopEngine();

    // Cleanup
    delete myManualCar;

    return 0;
}




///Completed OOPs
#include <iostream>
#include <string>

using namespace std;

// Base Car class
class Car {
    protected:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;

    public:
        Car(string brand, string model) {
            this->brand = brand;
            this->model = model;
            this->isEngineOn = false;
            this->currentSpeed = 0;
        }

        //Common methods for All cars.
        void startEngine() {
            isEngineOn = true;
            cout << brand << " " << model << " : Engine started." << endl;
        }

        void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            cout << brand << " " << model << " : Engine turned off." << endl;
        }

        virtual void accelerate() = 0;  // Abstract method for Dynamic Polymorphism

        virtual void accelerate(int speed) = 0;  //Abstract method for Static Polymorphism

        virtual void brake() = 0;       // Abstract method for Dynamic Polymorphism
        
        virtual ~Car() {}               // Virtual destructor
};

class ManualCar : public Car {
    private:
        int currentGear;

    public:
        ManualCar(string brand, string model) : Car(brand, model) {
            this->currentGear = 0;
        }

        //Specialized method for Manual Car
        void shiftGear(int gear) {
            currentGear = gear;
            cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
        }

        // Overriding accelerate - Dynamic Polymorphism
        void accelerate() {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            currentSpeed += 20;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
        }

        //overriding and overloading accelerate at the same time.
        void accelerate(int speed) {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            currentSpeed += speed;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
        }

        // Overriding brake - Dynamic Polymorphism
        void brake() {
            currentSpeed -= 20;
            if (currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
        }
    };

    class ElectricCar : public Car {
    private:
        int batteryLevel;

    public:
        ElectricCar(string brand, string model) : Car(brand, model) {
            this->batteryLevel = 100;
        }

        //specialized method for Electric Car
        void chargeBattery() {
            batteryLevel = 100;
            cout << brand << " " << model << " : Battery fully charged!" << endl;
        }

        // Overriding accelerate - Dynamic Polymorphism
        void accelerate() {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            if (batteryLevel <= 0) {
                cout << brand << " " << model << " : Battery dead! Cannot accelerate." << endl;
                return;
            }
            batteryLevel -= 10;
            currentSpeed += 15;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
        }

        // Overriding accelerate - Dynamic Polymorphism
        void accelerate(int speed) {
            if (!isEngineOn) {
                cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
                return;
            }
            if (batteryLevel <= 0) {
                cout << brand << " " << model << " : Battery dead! Cannot accelerate." << endl;
                return;
            }
            batteryLevel -= 10 + speed;
            currentSpeed += speed;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
        }

        // Overriding brake - Dynamic Polymorphism
        void brake() {
            currentSpeed -= 15;
            if (currentSpeed < 0) currentSpeed = 0;
            cout << brand << " " << model << " : Regenerative braking! Speed is now " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
        }
};

int main() {
    Car* myManualCar = new ManualCar("Ford", "Mustang");
    myManualCar->startEngine();
    myManualCar->accelerate();
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();

    cout << "----------------------" << endl;

    Car* myElectricCar = new ElectricCar("Tesla", "Model S");
    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->accelerate();
    myElectricCar->brake();
    myElectricCar->stopEngine();

    // Cleanup
    delete myManualCar;
    delete myElectricCar;

    return 0;
}