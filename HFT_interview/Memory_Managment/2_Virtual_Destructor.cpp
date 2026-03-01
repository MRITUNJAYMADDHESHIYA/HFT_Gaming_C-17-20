//Question:- How to avoid memory leaks with virtual destructors when using inheritance in c++

// once an inheritance hierarchy is created, with memory allocations occurring at each stage in the hierarchy, 
// it is necessary to be very careful about how objects are destroyed so that any memory leaks are avoided. 
// In order to achieve this, we make use of a virtual destructor.

//a virtual destructor ensures that when derived subclasses go out of scope or are deleted the order of destruction of each class in a hierarchy is carried out correctly. 
//If the destruction order of the class objects is incorrect, in can lead to what is known as a memory leak.


class Base{
    public:
        Base();
        ~Base();
};

class Derived : public Base{
    private:
        double val;
    public:
        Derived(const double& _val);
        ~Derived();
};

void do_something(){
    //a pointer p to a Base class is created and a reference to a new Derived class is assigned to it.
    Base* p = new Derived;

    //when we delete p the compiler only knows to call Base's destructor as the pointer is pointing to a Base class. 
    //The destructor associated with Derived is not called and val is not deallocated.
    delete p;
}




class Base {
    public:
        Base();
        virtual ~Base();
};

class Derived : public Base {
    private:
        double val;
    public:
        Derived(const double& _val);
        virtual ~Derived();
};

void do_something() {
    Base* p = new Derived;
    // Derived destructor is called
    //At code execution-time, the correct destructor is looked up in an object known as a vtable. Hence the destructor associated with Derived will be called prior to a further call to the destructor associated with Base. 
    delete p;  
}