#include<iostream>
#include<variant>
using namespace std;

int main(){
    variant<int, double, string> data;

    data = 10;
    cout<< get<int>(data) <<endl;

    data = 3.13;
    cout<< get<double>(data) <<endl;

    data = "Mritunjay";
    cout<< get<string>(data) <<endl;

    return 0;
}
