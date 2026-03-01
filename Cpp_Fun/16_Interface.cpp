//Interface :- If you want to call as me then you have me functionality

#include<iostream>
#include<cmath>
using namespace std;

class IShape{
    public:
        virtual ~IShape() = default;
        virtual void draw() const = 0;
        virtual void area() const = 0;
};

class Circle: public IShape{
    double r;
    public:
        Circle(double radius): r(radius){}

        void draw() const override{
            cout<<"Drawing Circle with radius "<<r<<endl;
        }
        double area() const override{
            return M_PI*r*r;
        }
};

class Reactangle: public IShape{
    double w, h;
    public:
        Reactangle(double width, double height): w(width), h(height){}

        void draw() const override{
            cout<<"Drawing Reactangle (" << w <<"x" << h <<")"<<endl;
        }

        double area() const override{
            return w * h;
        }
};

int main(){
    Reactangle rect(2, 3);
    return 0;
}