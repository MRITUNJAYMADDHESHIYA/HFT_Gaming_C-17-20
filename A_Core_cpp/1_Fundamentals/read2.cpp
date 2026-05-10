///////// RAII(resource acquisition is initialization) /////////////////
//1.Constructor acquires resource ---> destructor automatically closes file
//2.smart pointers :- std::unique_ptr  + std::shared_ptr




class file{
    file* fp;

    public:
        file(const char* name){
            fp = fopen(name, "r");
        }

        ~file(){
            if(fp) fclose(fp);
        }
};

/////may skip unlock
m.lock();
so_work();
m.unlock();

//automatic unlock
std::lock_guard<std::mutex> lock(m);


//////////// Constructor and Destructor ////////////////////
//constructor-->initializes an object
//destructor-->cleans up object 

class A{
    int x, y;

    public:
    //constructors overloading
        A(){std::cout<<"Default constructor";}
        A(int a, int b){  //parameterized constructor
            x = a;
            y = b;
        }

        A(int a, int b) :x(a), y(b) {} //initialization list
};

/////////Deep and shallow copy ///////////////////////////////
//deep:-
//creates separate independent resource(seprate memory)
//STL use this copy method


//shallow:- (default copy by compiler)
//copies values directly --- including pointer address
//at the time of destructors run--> double delete happen
//changing one object affects other


class A{
    public:
        int* data;

        A(int v) {
            data = new int(v);
        }

        ~A(){
            delete data;
        }

        A(const A& other){
            data = new int(*other.data);
        }
};
