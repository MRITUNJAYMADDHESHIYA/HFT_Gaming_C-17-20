//1. Dangling Pointers:- A dangling pointer is a pointer that refers to a memory location that has already been deallocated or is invalid.
//int* ptr = new int(10);
// delete ptr;         // memory is deallocated
// *ptr = 5;           // dangling pointer used → Undefined behavior
//fixed:-
//Always set pointers to nullptr after deleting: or use smart pointers to avoid dangling pointers.
//int* ptr = new int(10);
//delete ptr;         // memory is deallocated
//ptr = nullptr;     // now ptr is safe to use



//2. Memory Leaks:- A memory leak occurs when a program allocates memory but fails to deallocate it, leading to increased memory usage over time.
//int* ptr = new int(10); // memory allocated
// // No delete ptr; here, so memory leak occurs
//fixed:-
// Match every new/malloc with delete/free.
// Use RAII (Resource Acquisition Is Initialization) with smart pointers:


//3.Race Conditions:-A race condition occurs in a multithreaded environment when two or more threads access shared data at the same time, and at least one thread modifies it → leading to unpredictable results.
//fixed:-
//Mutex: std::mutex, pthread_mutex_t
// Atomic variables: std::atomic<int>


//4.Fragmentation:- Memory fragmentation occurs when free memory is split into small, non-contiguous blocks(Extrnal), making it difficult to allocate larger blocks of memory(internal ).
//Free but unusable memory blocks can lead to inefficient memory usage.
//fixed:-
// Use memory pools or custom allocators to manage memory more efficiently.
// Use smart pointers to manage memory automatically and reduce fragmentation issues.
// Use standard containers like std::vector, std::list, etc., which manage memory automatically and reduce fragmentation issues.


//////////////////////////////////////////////////********************************************************* ///////////////////////////////////////////////////////
//1.1when to use stack memory (for small, short-lived objects) versus heap memory (for large or long-lived objects) is vital for writing efficient programs.
//Stack memory is automatically managed and faster, while heap memory requires manual management and is slower.
// Use stack memory for small, short-lived objects that do not require dynamic allocation.
// Use heap memory for large or long-lived objects that require dynamic allocation.


//1.2
//Memory leak:-
void memoryLeak() {
    int* ptr = new int(10); // memory allocated
    // No delete ptr; here, so memory leak occurs
}

//Dangling pointer:-
void danglingPointer() {
    int* ptr = new int(10);
    delete ptr;         // memory is deallocated
    // *ptr = 5;         // dangling pointer used → Undefined behavior
    ptr = nullptr;      // now ptr is safe to use
}

//1.3
//Smart Pointers:-(They provide automatic memory management, reducing the risk of memory leaks and dangling pointers.)
//std::unique_ptr:-(It represents exclusive ownership of a dynamically allocated object. When the unique_ptr goes out of scope, it automatically deletes the object it owns.)
std::unique_ptr<int> ptr1 = std::make_unique<int>(10);

//std::shared_ptr:-(It allows multiple pointers to share ownership of a dynamically allocated object. The object is deleted when the last shared_ptr pointing to it is destroyed.)
std::shared_ptr<int> ptr2 = std::make_shared<int>(20);
std::shared_ptr<int> ptr3 = ptr2; // ptr2 and ptr3 share ownership of the same object

//std::weak_ptr:-(It is used in conjunction with shared_ptr to avoid circular references. It does not affect the reference count of the shared_ptr it points to.)
std::shared_ptr<int> sharedPtr = std::make_shared<int>(30);
std::weak_ptr<int> weakPtr = sharedPtr; // weakPtr does not affect the reference count of sharedPtr



//RAII (Resource Acquisition Is Initialization):-
//RAII is a programming idiom that binds the lifecycle of resources (like memory, file handles, etc.) to the lifetime of objects. When an object goes out of scope, its destructor is called, automatically releasing the resources it holds.
// This helps prevent resource leaks and ensures that resources are properly cleaned up.

//Move Semantics and Resource Management:-
//Move semantics allow the transfer of ownership of resources from one object to another without copying, improving performance and resource management.
// In C++11 and later, move semantics are implemented using rvalue references and the std

//Custom Allocators and Memory Pools:-
//Custom allocators allow developers to define how memory is allocated and deallocated, providing more control over memory management.
// Memory pools are pre-allocated blocks of memory that can be used to efficiently manage memory for objects of the same type, reducing fragmentation and allocation overhead.
// They can be implemented using custom allocators or third-party libraries like Boost or TBB (Threading Building Blocks).



