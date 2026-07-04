#include<bits/stdc++.h>
using namespace std;

///shortest distance source to destination (weight non-uniform)
vector<int> dijkstra(int V, vector<vector<int>> adj[], int S){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> result(V, INT_MAX);

    result[S] = 0; //source distance is zero
    pq.push({0, S});

    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for(auto &vec : adj[node]){
            int adjNode = vec[0];
            int dist    = vec[1];

            if(d + dist < result[adjNode]){
                result[adjNode] = d + dist;
                pq.push({d + dist, adjNode});
            }
        }
    }
    return result;
}