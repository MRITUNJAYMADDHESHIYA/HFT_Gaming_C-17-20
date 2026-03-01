//Adding the const keyword after a function prototype indicates that the function does not modify the state of the object on which it is called. 



#include <iostream>

class MyClass {
public:
    MyClass(int value) : m_value(value) {}

    // Member function that doesn't modify the object's state
    int getValue() const {
        return m_value;
    }

    // Member function that modifies the object's state
    void setValue(int newValue) {
        m_value = newValue;
    }

private:
    int m_value;
};

int main() {
    const MyClass obj(5); // Creating a const object
    std::cout << "Value of obj: " << obj.getValue() << std::endl;

    // obj.setValue(10); // Error: Cannot call non-const member function on const object
    return 0;
}
