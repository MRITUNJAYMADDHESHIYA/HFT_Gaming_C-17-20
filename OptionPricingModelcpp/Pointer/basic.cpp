#include<iostream>
using namespace std;

//pointer is store the address of the variable.
int main(){
    int n = 5;
    cout<<&n<<endl;

    int* ptr = &n;
    cout<<ptr<<endl;
    cout<<*ptr<<endl;

    //assign another value
    *ptr = 10;
    cout<< *ptr<<endl;
    cout<<n <<endl;

    return 0;
}