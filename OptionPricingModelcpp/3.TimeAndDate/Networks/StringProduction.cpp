#include "StringProduction.hpp"
#include "Dictionary.hpp"

#include<algorithm>
#include<climits>
#include<map>
#include<set>
using namespace std;

StringProduction::StringProduction(Dictionary &d):
    m_dic(d)
{}

StringProduction::StringProduction(const StringProduction &p):
    m_dic(p.m_dic)
{}

StringProduction::~StringProduction()
{}

StringProduction &StringProduction::operator=(const StringProduction &p){
    if(&p != this){
        m_dic = p.m_dic;
    }
    return *this;
}


vector<int> StringProduction::recoverPath(int src, int dest, const vector<int> &P, vector<int> &path){
    int v = dest;
    while(v != src){
        path.push_back(v);
        v = P[v]; //it's like mark as a visited
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
}

void StringProduction::shortest_path(int src, int dest, int n, vector<string> &path){
    const vector<vector<bool>> &adj = m_dic.adjList(); //adjency matrix
    path.clear();

    vector<int> dist(n,0);
    vector<int> prev(n,0);
    set<int> st;
    const int INF = INT_MAX;

    for(int i=0; i<n; i++){
        st.insert(i);
        if(i != src){
            dist[i] = INF;
        }
    }

    while(!st.empty()){
        int min = INF;
        int u = -1;

        for(set<int>::iterator it=st.begin(); it != st.end(); ++it){
            //find mini value in st
            if(dist[*it] < min){
                min = dist[*it];
                u = *it;
            }
        }
        st.erase(u);

        for(int i=0; i<n; i++){
            if(adj[u][i]){
                int d = dist[u] + 1;
                if(d < dist[i]){
                    dist[i] = d;
                    prev[i] = u;
                }
            }
        }
    }

    vector<int> npath;
    recoverPath(src, dest, prev, npath);
    for(auto it: npath){
        path.push_back(m_dic.elemAtPos(it));
    }
}

// Returns true if the word src produces dest using the
// dictionary dic. If true, then path will contain the path
// between src and dest.

bool StringProduction::produces(const string &src, const string &dest, vector<string> &path){
    if(!m_dic.contains(src) || !m_dic.contains(dest)) return false;
    shortest_path(m_dic.elemPosition(src),m_dic.elemPosition(dest), m_dic.size(), path);
    return path.size()>0;
}