#include "RandomWalkGenerator.hpp"
#include<iostream>
#include<cstdlib>

//using std::vector;
using std::cout;
using std::endl;

RandomWalk::RandomWalk(int size, double start, double step):
    m_numSteps(size),
    m_stepSize(step),
    m_initialPrice(start)
{}

RandomWalk::RandomWalk(const RandomWalk &p):
    m_numSteps(p.m_numSteps),
    m_stepSize(p.m_stepSize),
    m_initialPrice(p.m_initialPrice)
{}

RandomWalk::~RandomWalk()
{}

RandomWalk &RandomWalk::operator=(const RandomWalk &p){
    if(this != &p){
        m_numSteps = p.m_numSteps;
        m_stepSize = p.m_stepSize;
        m_initialPrice = p.m_initialPrice;
    }
    return *this;
}


double RandomWalk::computeRandomStep(double currentPrice){
    const int num_direction = 3;  //buy, sell, consolidation
    int r = rand() % num_direction;
    double val = currentPrice;
    if(r==0){
        val += (m_stepSize * val);
    }else if(r==1){
        val -= (m_stepSize * val);
    }
    return val;
}

std::vector<double> RandomWalk::generateWalk(){
    std::vector<double> walk;
    double prev = m_initialPrice;

    for(int i=0; i<m_numSteps; i++){
        double val = computeRandomStep(prev);
        walk.push_back(val);
        prev = val;
    }
    return walk;
}


int main(){
    RandomWalk rw(100, 30, 0.01);
    std::vector<double> walk = rw.generateWalk();

    for(int i=0; i<walk.size(); i++){
        cout<<", "<<i<<", "<<walk[i]<<endl;
    }
    cout<<endl;
    return 0;
}