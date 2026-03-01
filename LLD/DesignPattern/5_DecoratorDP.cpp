//Decorator pattern attaches additional responsibilities to an object dynamically Decorator provides a flexible
//alternative to subclassing for extending functionality.

//Adds behavior at runtime, without modifying the original class.
//Using aggregation, not inheritance

//RealWorld:-
//1.Text Decorator-->bold then italic
//


//UML:-(mario character)
//
//  <<abstract>>
// ICharacter(getAbitities())
//   |       |              |
//   |       | is a         | has a
//   |       | <<abstract>> |
//   |       Decorator(getAbilities())<-----HeightUpDec(Icharacter ch, getAbilities())
//   |                                |-----GunPowerDec(Icharacter ch, getAbilities())
// Mario(getAbilities())              |-----StorPowerDec(Icharacter ch, getAbilities())
// 


#include<iostream>
#include<string>
using namespace std;

///A common interface for mario and all power-up decorators
class Character{
    public:
        virtual string getAbilities() const = 0;
        virtual ~Character() {}
        //If you delete a derived object through a base class pointer, the base destructor must be virtual, otherwise only the base destructor runs → causing memory leak or partial destruction.
};

class Mario : public Character{
    public:
        string getAbilities() const override{
            return "Mario";
        }
};

//CharacterDecorator "is-a" character and "has-a" character
class CharacterDecorator : public Character{
    protected:
        Character* character;
    public:
        CharacterDecorator(Character* c){
            this->character = c;
        }
};


class HeightUp : public CharacterDecorator{
    public:
        HeightUp(Character* c) : CharacterDecorator(c){}

        string getAbilities() const override{
            return character->getAbilities() + " with heightUp";
        }
};

class GunPowerUp : public CharacterDecorator{
    public:
        GunPowerUp(Character* c) : CharacterDecorator(c){}

        string getAbilities() const override{
            return character->getAbilities() + " with Gun";
        }
};

class StarPower : public CharacterDecorator{
    public:
        StarPower(Character* c) : CharacterDecorator(c) {}

        string getAbilities() const override{
            return character->getAbilities() + " with Star Power(Limited power)";
        }

        ~StarPower(){
            cout<<"Destroying StarPower Decorator"<<endl;
        }
};


int main(){
    //mario character
    Character* mario = new Mario();
    cout<< "Basic Character: "<< mario->getAbilities()<<endl;

    //heightUp
    mario = new HeightUp(mario);
    cout<<"After HeightUp: "<< mario->getAbilities() << endl;

    //GunPower
    mario = new GunPowerUp(mario);
    cout<< "After GunPowerup: "<< mario->getAbilities() << endl;

    mario = new StarPower(mario);
    cout<< "After StarPower: "<< mario->getAbilities() << endl;

    delete mario;

    return 0;
}





