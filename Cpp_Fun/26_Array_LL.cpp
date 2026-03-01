//1.Frequent Insertion and Deletion
//In arrays, inserting or deleting an element requires shifting other elements, leading to O(n) time complexity. 
//Linked lists allow for O(1) time complexity for these operations if the position is known.(just change pointers)



//2.Unpredictable Size
//Arrays have a fixed size determined at compile-time or during dynamic allocation.
//Linked lists can grow and shrink dynamically as needed, making them more flexible for situations where the size is unpredictable.

//3.Constant time insert at beginning
//adding to the head of a linked list is O(1) operation, while in an array it is O(n) because all elements need to be shifted.

//Linked lists lose on random access and cache locality.

//use LL when you modify data often
//use array when you need fast access to elements using index and read data often

