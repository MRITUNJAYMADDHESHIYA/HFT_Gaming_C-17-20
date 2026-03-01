#ifndef __StringProduction__StringProduction__
#define __StringProduction__StringProduction__

#include<vector>
#include<string>
using namespace std;


class Dictionary;
class StringProduction{
    public:
        StringProduction(Dictionary &d);
        StringProduction(const StringProduction &p);
        ~StringProduction();
        StringProduction &operator=(const StringProduction &p);

        bool produces(const string &src, const string &dest, vector<string> &path);
        void shortest_path(int v, int dest, int n, vector<string> &path);
        vector<int> recoverPath(int src, int dest, const vector<int> &P, vector<int> &path);

    private:
        Dictionary &m_dic;
};

#endif