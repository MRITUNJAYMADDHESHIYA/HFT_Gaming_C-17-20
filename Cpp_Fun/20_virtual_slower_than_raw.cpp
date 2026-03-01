//why virtual function is slower than raw function

//virtual function allow runtime polymorphism, meaning the function to call is decided at runtime, not compile time.
//virtual functions has a vtable, each object stores a vptr pointing to it's class vtable

//when we call a virtual funtion, the program looks up the function address in the vtable.
