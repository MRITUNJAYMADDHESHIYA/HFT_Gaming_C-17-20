#include<bits/stdc++.h>
using namespace std;

/////shortest distance source to destination(0_1_weight edge)
vector<int> 0_1_BFS(int n, vector<vector<int>> adj[], int S){
    deque<pait<int, int>> dq;
    vector<int> result(n, INT_MAX);

    result[S] = 0;
    dq.push_front({0, 0}); //weigth, node

    while(!dq.empty()){
        auto [cost, node] = dq.pop_front();

        for(auto &ngbr : adj[node]){
            if(cost + wt < result[ngbr]){
                result[ngbr] = cost + wt;

                if(wt == 0){
                    dq.push_front();
                }else{
                    dq.push_back();
                }
            }
        }
    }
    return result;
}
