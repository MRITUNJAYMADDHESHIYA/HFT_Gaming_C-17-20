//1.change and not change  something in class must be seprate

//////Why inheritance is Bad?
//1.Robot-->walk(); talk(); projection();
//1.a.CompanionR-->projection();
//1.b.WorkerR-->projection();

//1.c.SparrowR-->projection(); but it can fly()
//1.d.CrowR----->projection(); but it can fly()
/////it break the DRY(don't repeat principle)
////we can use the hirarchi inheritance but it's not good


//////Strategy Design Pattern
//A family of algorithm, put them into seprate classes so that they can be changed at runtime.

//1.Robot-->talkable t, walkable w, flyable f  and projection();
//1.a.Talkable-->talk()   ///abstract
//1.b.Walkable-->walk()   ///abstract
//1.c.Flyable-->fly()     ///abstract

//1.a.a.NormalTalk-->talk()
//1.a.b.NoTalk-->talk()

//1.b.a.NormalWalk--->walk()
//1.b.b.NoWalk-->walk()

//1.c.a.NormalFly-->fly()
//1.c.b.NoFly-->fly()

#include<iostream>
using namespace std;

///////Strategy class(walk,talk,fly)
////////Walk Interface
class WalkableRobot{
    public:
        virtual void walk() = 0;
        virtual ~WalkableRobot() {}
};

class NormalWalk : public WalkableRobot{
    public:
        void walk() override{
            cout<< "Walking normally..."<<endl;
        }
};

class NoWalk : public WalkableRobot{
    public:
        void walk() override{
            cout<<"Cannot walk."<<endl;
        }
};

///////Talk Interface
class TalkableRobot{
    public:
        virtual void talk() = 0;
        virtual ~TalkableRobot() {}
};

class NormalTalk : public TalkableRobot{
    public:
        void talk() override{
            cout<<"Talking normally..."<<endl;
        }
};

class NoTalk : public TalkableRobot{
    public:
        void talk() override{
            cout<<"Cannot talk."<<endl;
        }
};

///////Fly Interface
class FlyableRobot{
    public:
        virtual void fly() = 0;
        virtual ~FlyableRobot() {}
};

class NormalFly : public FlyableRobot{
    public:
        void fly() override{
            cout<<"Flying normally..."<<endl;
        }
};

class NoFly : public FlyableRobot{
    public:
        void fly() override{
            cout<<"Cannot fly."<<endl;
        }
};


////////////Robot Base class(client class)
class Robot{
    protected:
        WalkableRobot* walkBehaviour;
        TalkableRobot* talkBehaviour;
        FlyableRobot*  flyBehaviour;
    public:
        Robot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f){
            this->walkBehaviour = w;
            this->talkBehaviour = t;
            this->flyBehaviour  = f;
        }

        //these function only delicate in the own interfaces
        void walk(){
            walkBehaviour->walk();
        }
        void talk(){
            talkBehaviour->talk();
        }
        void fly(){
            flyBehaviour->fly();
        }

        virtual void projection() = 0;
};


class CompanionRobot : public Robot{
    public:
        CompanionRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f) : Robot(w, t, f) {}

        void projection() override{
            cout<<"Displaying friendly companion features..."<<endl;
        }
};

class WorkerRobot : public Robot{
    public:
        WorkerRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f): Robot(w, t, f) {}

        void projection() override{
            cout<<"Displaying worker efficiency stats..."<<endl;
        }
};

int main(){
    Robot* robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

    cout<<"This is the end/..............."<<endl;

    Robot* robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();

    return 0;
}