//Define an interface for creating objects but allows subclasses to decide which class to instantiate.
//1.Factory->simple  + Factory + abstract factory method

//////////Simple factory method
//1.Burger-->prepare();
//1.a.basicBurger
//1.b.standerdBurger
//1.c.premiumBurger

//2.BurgerFactory-->createBurger(type)
#include<iostream>
using namespace std;

class Burger{
    public:
        virtual void prepare() = 0;
        virtual ~Burger() {}
};

class BasicBurger : public Burger{
    public:
        void prepare() override{
            cout<<"Preparing Basic Burger"<<endl;
        }
};

class StandardBurger : public Burger{
    public:
        void prepare() override{
            cout<<"Preparing standerd Burgur"<<endl;
        }
};

class PremiumBurger : public Burger{
    public:
        void prepare() override{
            cout<<"Preparing Premium Burger"<<endl;
        }
};

class BurgerFactory{
    public:
        Burger* createBurger(string& type){
            if(type == "basic"){
                return new BasicBurger();
            }else if(type == "standard"){
                return new StandardBurger();
            }else if(type == "premium"){
                return new PremiumBurger();
            }else{
                cout<<"Invalid burgur type! "<<endl;
                return nullptr;
            }
        }
};

int main(){
    string type = "standard";
    BurgerFactory* myBurgerFactory = new BurgerFactory();

    Burger* burger = myBurgerFactory->createBurger(type);
    burger->prepare();

    return 0;
}


/////////Factory Method
class Burger1{
    public:
        virtual void prepare() = 0;
        virtual ~Burger() {}
};

class BasicBurger : public Burger1{
    public:
        void prepare() override{
            cout<<"Preparing Basic Burger"<<endl;
        }
};

class StandardBurger : public Burger1{
    public:
        void prepare() override{
            cout<<"Preparing standerd Burgur"<<endl;
        }
};

class PremiumBurger : public Burger1{
    public:
        void prepare() override{
            cout<<"Preparing Premium Burger"<<endl;
        }
};

class BasicWheatBurger : public Burger1{
    public:
        void prepare() override{
            cout<<"Preparing basic Wheat Burger"<<endl;
        }
};

class StanderdWheatBurger : public Burger1{
    public:
        void prepare() override{
            cout<<"Preparing standerd wheat Burger"<<endl;
        }
};

class PremiumWheatburger : public Burger1{
    public:
        void prepare() override{
            cout<<"preparing Premium wheat Burger"<<endl;
        }
};

/////Factory and its concretions
class BurgerFactory1{
    public:
        virtual Burger1* createBurger(string& type) = 0;
};

class SinghBurger : public BurgerFactory1{
    public:
        Burger1* createBurger(string& type) override{
            if(type == "Basic"){
                return new BasicBurger();
            }else if(type == "Standerd"){
                return new StandardBurger();
            }else if(type == "Premium"){
                return new PremiumBurger();
            }else{
                cout<<"Invalid burger type! "<<endl;
                return nullptr;
            }
        }
};

class kingBurger : public BurgerFactory1{
    public:
        Burger1* createBurger(string& type) override{
            if(type == "Basic"){
                return new BasicWheatBurger();
            }else if(type == "Standerd"){
                return new StanderdWheatBurger();
            }else if(type == "Premium"){
                return new PremiumWheatburger();
            }else{
                cout<<"Invalid burger type! "<<endl;
                return nullptr;
            }
        }
};

int main(){
    string type = "Premium";
    BurgerFactory1* myFactory = new kingBurger();

    Burger1* burger = myFactory->createBurger(type);
    burger->prepare();

    return 0;
}



//////////abstract Factory method
class Burger2{
    public:
        virtual void prepare() = 0;
        virtual ~Burger2() {}
};

class BasicBurger : public Burger2{
    public:
        void prepare() override{
            cout<<"Preparing Basic Burger"<<endl;
        }
};

class StandardBurger : public Burger2{
    public:
        void prepare() override{
            cout<<"Preparing standerd Burgur"<<endl;
        }
};

class PremiumBurger : public Burger2{
    public:
        void prepare() override{
            cout<<"Preparing Premium Burger"<<endl;
        }
};

class BasicWheatBurger : public Burger2{
    public:
        void prepare() override{
            cout<<"Preparing basic Wheat Burger"<<endl;
        }
};

class StanderdWheatBurger : public Burger2{
    public:
        void prepare() override{
            cout<<"Preparing standerd wheat Burger"<<endl;
        }
};

class PremiumWheatburger : public Burger2{
    public:
        void prepare() override{
            cout<<"preparing Premium wheat Burger"<<endl;
        }
};

class GarlicBread{
    public:
        virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread{
    public:
        void prepare() override{
            cout<<"Preparing Basic Garlic Bread"<<endl;
        }
};

class CheeseGarlicBread : public GarlicBread{
    public:
        void prepare() override{
            cout<<"Preparing Cheese Garlic Bread"<<endl;
        }
};

class BasicWheatGarlicBread : public GarlicBread{
    public:
        void prepare() override{
            cout<<"Preparing basic Wheat Garlic Bread"<<endl;
        }
};

class CheeseWheatGarlicBread : public GarlicBread{
    public:
        void prepare() override{
            cout<<"Preparing cheese wheat Garlic Bread"<<endl;
        }
};


////
class MealFactory{
    public:
        virtual Burger2* createBurger(string& type) = 0;
        virtual GarlicBread* createGarlicBread(string& type) = 0;
};

class SinghBurger : public MealFactory{
    public:
        Burger2* createBurger(string& type) override{
            if(type == "Basic"){
                return new BasicBurger();
            }else if(type == "Standard"){
                return new StandardBurger();
            }else if(type == "Premium"){
                return new PremiumBurger();
            }else{
                cout<<"Invalid burger type!"<<endl;
                return nullptr;
            }
        }

        GarlicBread* createGarlicBread(string& type) override{
            if(type == "Basic"){
                return new BasicGarlicBread();
            }else if(type == "Cheese"){
                return new CheeseGarlicBread();
            }else{
                cout<<"Invalid Garlic bread type! "<<endl;
                return nullptr;
            }
        }
};

class kingBurger : public MealFactory{
    public:
        Burger2* createBurger(string& type) override{
            if(type == "Basic"){
                return new BasicWheatBurger();
            }else if(type == "Standard"){
                return new StanderdWheatBurger();
            }else if(type == "Premium"){
                return new PremiumWheatburger();
            }else{
                cout<<"Invalid Burger type! "<<endl;
                return nullptr;
            }
        }

        GarlicBread* createGarlicBread(string& type) override{
            if(type == "Basic"){
                return new BasicWheatGarlicBread();
            }else if(type == "Cheese"){
                return new CheeseWheatGarlicBread();
            }else{
                cout<<"Invalid Garlic bread type!"<<endl;
                return nullptr;
            }
        }
};

int main(){
    string burgerType = "Basic";
    string garlicBreadType = "Cheese";

    MealFactory* mealFactory = new kingBurger();

    Burger2* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread = mealFactory->createGarlicBread(garlicBreadType);

    burger->prepare();
    garlicBread->prepare();

    return 0;
}