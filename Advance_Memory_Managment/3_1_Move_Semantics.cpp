//A move constructor is used to transfer ownership of resources from one object to another. Instead of copying the resources,

// T(T&&) → Move constructor
// T& operator=(T&&) → Move assignment operator

#include <iostream>
#include <utility> // for std::move

class Buffer {
private:
    int* data_;
    size_t size_;

public:
    //Constructor
    Buffer(size_t size) : size_(size) {
        data_ = new int[size];
        std::cout << "Constructor: allocated " << size_ << " ints\n";
    }

    //Destructor
    ~Buffer() {
        delete[] data_;
        std::cout << "Destructor: released memory\n";
    }

    //Copy Constructor
    Buffer(const Buffer& other) : size_(other.size_) {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Copy Constructor: deep copy\n";
    }

    //Move Constructor (C++11)
    Buffer(Buffer&& other) noexcept : data_(nullptr), size_(0) {
        std::cout << "Move Constructor\n";
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }

    //Move Assignment Operator (C++11)
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "Move Assignment Operator\n";
        if (this != &other) {
            delete[] data_; // Clean up
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void print() const {
        std::cout << "Buffer size: " << size_ << "\n";
    }
};

Buffer createBuffer() {
    Buffer temp(10);
    return temp; //Move constructor will be used here (C++11/17)
}

int main() {
    Buffer buf1 = createBuffer();   //Move constructor
    Buffer buf2(5);
    buf2 = createBuffer();          //Move assignment operator
}
