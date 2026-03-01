//interface segregation principle
//many client specific interface are better then one general purpose interface.
//client should not be forced to implement methods they don't need

//example:- 2-D and 3-D shape

#include<iostream>
#include<stdexcept>

class Shape{
    public:
        virtual double area() = 0;
        virtual double volume() = 0; //2-D don't have volume
};

//force to implement the volume
class Square : public Shape{
    private:
        double side;
    public:
        Square(double s) : side(s) {}

        double area() override{
            return side * side;
        }

        double volume() override{
            throw std::logic_error("Volume not applicable for squre");
        }
};

class Reactangle : public Shape{
    private:
        double length, width;
    public:
        Reactangle(double l, double w) : length(l), width(w) {}

        double area() override{
            return length*width;
        }

        double volume() override{
            throw std::logic_error("Volume not applicable for Reactangle");
        }
};

class Cube : public Shape{
    private:
        double side; 
    public:
        Cube(double s) : side(s) {}

        double area() override{
            return 6 * side * side;
        }

        double volume() override{
            return side * side * side;
        }
};

int main(){
    Shape* square = new Square(5);
    Shape* reactangle = new Reactangle(4, 6);
    Shape* cube = new Cube(4);

    std::cout<<"Squre Area: "<< square->area() <<std::endl;
    std::cout<<"Reactangle Area: "<< reactangle->area() <<std::endl;
    std::cout<<"Cube Area: "<< cube->area() <<std::endl;
    std::cout<<"cube volume: "<< cube->volume() <<std::endl;

    try{
        std::cout<<"Square Volume: "<<square->volume() << std::endl;
    }catch(std::logic_error& e){
        std::cout<< "Exceptions: "<<e.what() <<std::endl;
    }

    return 0;
}


//////////////solution ////////////////////////////
class TwoDimensionalShape{
    public:
        virtual double area() = 0;
};

class ThreeDimensionalShape{
    public:
        virtual double area() = 0;
        virtual double volume() = 0;
};

class Squre : public TwoDimensionalShape{
    private:
        double side;
    public:
        Square(double s) : side(s) {}

        double area() override{
            return side * side;
        }
};

class Cube : public ThreeDimensionalShape{
    private:
        double side;
    public:
        Cube(double s) : side(s) {}

        double area() override{
            return 6 * side * side;
        }

        double volume() override{
            return side * side * side;
        }
};