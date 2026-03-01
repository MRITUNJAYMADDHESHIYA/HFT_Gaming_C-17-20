#ifndef __StringProduction__Dictionary__
#define __stringProduction__Dictionary__

#include<string>
#include<vector>
#include<map>
using namespace std;

class Dictionary{
    public:
        Dictionary(int wordSize);
        ~Dictionary(){}
        Dictionary &operator=(const Dictionary &p);
    private:
        Dictionary(const Dictionary &p);

    public:
        void addElement(const std::string &s);
        void buildAdjencyMatrix();
        bool contains(const std::string &s);
        const std::vector<std::vector<bool>> &adjList();
        int elemPosition(const std::string &s);
        int size() {return (int)m_values.size(); }
        string elemAtPos(int i);
    private:
        vector<string> m_values;
        map<string, int> m_valuePositions;
        vector<vector<bool> > m_adjacencyList;
        int m_wordSize;
};



#endif