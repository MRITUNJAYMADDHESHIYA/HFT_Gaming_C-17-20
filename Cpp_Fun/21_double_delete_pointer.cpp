//If we call delete again on the same pointer
//that memory already freed, we are trying to free twice



int * p = new int(10);
delete p;
delete p; // undefined behavior
//how to avoid double delete
//set pointer to null after delete
p = nullptr;