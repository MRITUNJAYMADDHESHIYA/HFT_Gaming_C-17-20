#include "Dictionary.hpp"
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;

Dictionary::Dictionary(int wordSize):
    m_values(),
    m_valuePositions(),
    m_adjacencyList(),
    m_wordSize(wordSize)
{}

const vector<vector<bool>> &Dictionary::adjList(){
    return m_adjacencyList;
}

Dictionary &Dictionary::operator=(const Dictionary &p){
    if(&p != this){
        m_adjacencyList = p.m_adjacencyList;
        m_valuePositions = p.m_valuePositions;
        m_values = p.m_values;
        m_wordSize = p.m_wordSize;
    }
    return *this;
}

// True if the words a and b differ by just one character
bool diffByOne(const string &a, const string &b){
    if(a.size() != b.size()) return false;
    int ndiff = 0;
    for(unsigned i=0; i<a.length(); i++){
        if(a[i] != b[i]) ndiff++;
    }
    return ndiff == 1;
}

//string contain in the map
bool Dictionary::contains(const string &s){
    return m_valuePositions.find(s) != m_valuePositions.end();
}

int Dictionary::elemPosition(const string &s){
    return m_valuePositions[s];
}

//add new word in dictionary
void Dictionary::addElement(const string &s){
    if(s.size() != m_wordSize){
        throw runtime_error("invalid string size");
    }

    m_values.push_back(s);
    m_valuePositions[s] = (int)m_values.size()-1;
    cout<< " added "<<s <<endl;
}

string Dictionary::elemAtPos(int i){
    return m_values[i];
}

void Dictionary::buildAdjencyMatrix(){
    m_adjacencyList.clear();
    int n = (int)m_values.size();
    for(int i=0; i<n; i++){
        m_adjacencyList.push_back(vector<bool>(n));
        for(int j=0; j<n; j++){
            if(diffByOne(m_values[i], m_values[j])){
                m_adjacencyList[i][j] = true;
            }
        }
    }
}