//1.Stack Memory:-(small, automatic, fast)
int arr[1000000000000] //big array on stack likely overflow



//2.Heap Memory:-(large, manual, flexible)
int* arr = new int[10000000000] //good for dynamic memory(heap)
delete [] arr;


//Does memory leak exist even after program terminates?
//No,modern OS reclaims all memory allocated by program after its termination


