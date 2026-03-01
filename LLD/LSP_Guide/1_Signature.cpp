//1.signature rule:- broad(parent) and narrow(child)

//////Method Argument rule
#include<iostream>
#include<vector>
#include<stdexcept>

class Parent{
    public:
        virtual void print(string msg){
            std::cout<< "Parent: " << msg <<std::endl;
        }
};

class Child : public Parent{
    public:
        void print(string msg) override {
            std::cout<< "Child: " << msg <<std::endl;
        }
};

class Client{
    private:
        Parent* p;
    public:
        Client(Parent* parent): p(parent) {}

        void execute(){
            p->print("Hello, World!");
        }
};

int main(){
    Parent* parent = new Parent();
    Parent* child  = new Child();

    //Client* client1 = new Client(parent); //using Parent object
    Client* client = new Client(child); //using Child object where Parent is expected

    client->execute();

    return 0;
}


///////////////Return type rule
//child class return same or narrow return(override function)

class Animal{
    //some animal methods
};

class Dog : public Animal{
    //some dog methods
};


class Parent{
    public:
        virtual Animal* getAnimal(){
            std::cout<< "Parent getAnimal" <<std::endl;
            return new Animal();
        }
};

class Child : public Parent{
    public:
        //it can be animal or dog
        Animal* getAnimal() override {
            std::cout<< "Child getAnimal" <<std::endl;
            return new Dog();
        }

        Dog* getAnimal() override {
            std::cout<< "Child getAnimal" <<std::endl;
            return new Dog();
        }
};


class Client{
    private:
        Parent* p;
    public:
        Client(Parent* parent): p(parent) {}

        void execute(){
            Animal* a = p->getAnimal();
            //use animal
        }
};

int main(){
    Parent* parent = new Parent();
    Parent* child  = new Child();

    //Client* client1 = new Client(parent); //using Parent object
    Client* client = new Client(child); //using Child object where Parent is expected

    client->execute();

    return 0;
}



//////////////Exception Rule
//same child class error same or narrow error

//logic_error -> invalid_argument, domain_error, length_error, out_of_range
//runtime_error -> range_error, overflow_error, underflow_error


class Parent{
    public:
        virtual void getValue() noexcept(false){
            throw logic_error("Parent logic error");
        }
};

class Child : public Parent{
    public:
        void getValue() noexcept(false) override {
            throw invalid_argument("Child invalid argument error");
        }
};

class Client{
    private:
        Parent* p;
    public:
        Client(Parent* parent): p(parent) {}

        void execute(){
            try{
                p->getValue();
            }
            catch(const logic_error& e){
                std::cout<< "Caught logic_error: " << e.what() <<std::endl;
            }
        }
};

int main(){
    Parent* parent = new Parent();
    Parent* child  = new Child();

    //Client* client1 = new Client(parent); //using Parent object
    Client* client = new Client(child); //using Child object where Parent is expected

    client->execute();

    return 0;
}