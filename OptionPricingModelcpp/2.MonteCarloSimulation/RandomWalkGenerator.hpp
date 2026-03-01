#ifndef __CppOption__RandomWalkGenerator__
#define __CppOption__RandomWalkGenerator__

#include<vector>
//using namespace std;

class RandomWalk{
    public:
        RandomWalk(int size, double start, double step);
        RandomWalk(const RandomWalk &p);
        ~RandomWalk();
        RandomWalk &operator = (const RandomWalk &p);

        //implementing the function in main.cpp
        std::vector<double> generateWalk();
        double computeRandomStep(double currentPrice);

    private:
        int m_numSteps;
        double m_stepSize; //in precent
        double m_initialPrice;
};

#endif