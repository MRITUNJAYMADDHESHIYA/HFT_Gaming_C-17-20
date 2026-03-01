#include<iostream>
using namespace std;

class A{
        int _num{};
    public:
        void setNum(int num) {_num = num;}
        //void setNum(int num) const {_num = num;}
        int getNum() const noexcept {return _num; }
};

int main(){
    A a;
    cout<< a.getNum() << endl;

    a.setNum(10);
    cout<< a.getNum() << endl;

    return 0;
}