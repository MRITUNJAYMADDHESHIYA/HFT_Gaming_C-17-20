#include<iostream>

// Operation	             When Called                               	Purpose	            Example
// Copy Constructor	         New object created from existing one	Initialize new object	A a2 = a1;
// Copy Assignment Operator	 Existing object assigned another	    Replace content	        a2 = a1;
// Move Constructor	         Transfer ownership to new object	    Steals resource (fast)	A b = std::move(a);
// Move Assignment	         Transfer ownership to existing object	Steals resource (fast)	b = std::move(a);
class Demo{
    int* data;
    public:
        //rule of three(Destructor + copy + copy assignment operator)
        ~Demo() {delete data:}
        Demo(const Demo& other) : data(new int(*other.data)){}
        Demo& operator=(const Demo& other){
            if(this != &other) *data = *other.data;
            return *this;
        }

        //Rule of Five(move and move assignment operator)
        Demo(Demo&& other) noexcept: data(other.data){ //data(other.data) — just steal the pointer from other(no copy, no allocation)
            other.data = nullptr; //when its destructor runs, it won’t delete the same memory twice.
        }

        Demo& operator=(Demo&& other) noexcept{
            if(this != &other){
                delete data;          //free the old resource
                data  = other.data;   //take ownership of the new one
                other.data = nullptr; //prevent double delete
            }
            return *this;
        }
};