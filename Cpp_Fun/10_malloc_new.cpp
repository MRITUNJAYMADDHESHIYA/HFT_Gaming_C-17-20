//malloc : memory allocation in heap segment
//new    : memory allocation in heap segment and calls constructor



//How dynamic memory allocation works in C++?
MyClass* obj = new MyClass(); //allocates memory and calls constructor
//1.memory allocation
void* mem = operator new(sizeof(MyClass));
//2.constructor call
MyClass* obj = new(mem) MyClass();



//malloc -> return a void pointer
MyClass* obj = (MyClass*)malloc(sizeof(MyClass));
//new
MyClass* obj = new MyClass();



int x = 10; //static memory allocation
int* arr = new int[size]; //dynamic memory allocation

