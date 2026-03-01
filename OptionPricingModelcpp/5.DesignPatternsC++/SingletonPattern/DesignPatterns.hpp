//there is only one object of that class in the application. 

#ifndef DesignPatterns_hpp
#define DesignPatterns_hpp

using namespace std;
class Trade{
    //somthing 
};

class ClearingHouse{
    private:
        ClearingHouse();
        ClearingHouse(const ClearingHouse &p);
        ~ClearingHouse();
        ClearingHouse &operator=(const ClearingHouse &p);

    public:
        static ClearingHouse &getClearingHouse();
        void clearTrade(const Trade &);

    private:
        static ClearingHouse *s_clearingHouse;

};

#endif