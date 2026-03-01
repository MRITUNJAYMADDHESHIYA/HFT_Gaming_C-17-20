#include<iostream>
using namespace std;

void printNumber(int* numberPtr){
    cout<< *numberPtr <<endl;
}
void printChar(char* charPtr){
    cout<< *charPtr <<endl;
}

//any data-type
void print(void* ptr, char type){
    switch(type){
        case 'i': cout<< *((int*)ptr)<< endl; break; //handle int*
        case 'c': cout<< *((char*)ptr)<< endl; break; //handle char*
    }
}
int main(){
    int number = 5;
    char letter = 'a';

    // printNumber(&number);
    // printChar(&letter);
    print(&number,  'i');
    print(&letter,  'c');

    return 0;
}