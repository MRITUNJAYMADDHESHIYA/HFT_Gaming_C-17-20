//I have implemented a simple vector class in c++ that mimics the bahavior of str::vector



#include<iostream>
#include<stdexcept> //for std::out_of_range
#include<cstddef> //for size_t

template<typename T>
class MyVector{
    private:
        T* data;
        size_t _size;   //current elements
        size_t _capacity;//maximum elements that can be stored without resizin

        void resize(size_t new_capacity){
            T* new_data = new T[new_capacity]; //dynamically allocate new array
            for(size_t i=0; i<_size; ++i){
                new_data[i] = data[i]; //copy old elements to new array
            }
            delete[] data; //free old array
            data = new_data; //point to new array
            _capacity = new_capacity; //update capacity
        }

    public:
        MyVector(): data(nullptr), _size(0), _capacity(0) {}

        ~MyVector(){
            delete[] data;
        }

        void push_back(const T& value){
            if(_size == _capacity){   //if max capacity is reached
                // Double the capacity or set to 1 if it was 0
                size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
                resize(new_capacity);
            }
            data[_size++] = value;
        }

        void pop_back(){
            if(_size > 0){
                --_size; //decrease size
            }
        }

        size_t size() const {
            return _size; //return current size
        }

        size_t capacity() const {
            return _capacity; //return current capacity
        }

        bool empty() const {
            return _size == 0; //check if vector is empty
        }

        //modifiable and const access to elements
        T& operator[](size_t index){
            if(index >= _size) throw std::out_of_range("Index out of range");
            return data[index]; //return element at index
        }

        //non-modifiable
        const T& operator[](size_t index) const {
            if(index >= _size) throw std::out_of_range("Index out of range");
            return data[index]; //return element at index
        }

};

int main(){
    MyVector<int> vec;

    std::cout<<"Pushing values: ";
    for(int i=0; i<=5; ++i){
        vec.push_back(i);
        std::cout<<i<<" ";
    }

    std::cout<<"\nSize: "<<vec.size();
    std::cout<<"\nCapacity: "<<vec.capacity();

    std::cout<<"\nElements: ";
    for(size_t i=0; i<vec.size(); ++i){
        std::cout<<vec[i]<<" ";
    }

    vec.pop_back(); //remove last element
    std::cout<<"\nAfter pop_back, Size: "<<vec.size();
    std::cout<<"\nAfter pop_back, capacity: "<<vec.capacity();
    std::cout<<std::endl;
    return 0;
}