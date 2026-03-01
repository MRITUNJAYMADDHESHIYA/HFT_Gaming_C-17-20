#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;

        vector<int> a(n);
        for(int i=0; i<n; i++) cin >> a[i];

        bool flag = false; //find out the sepration or not
        for(int i=m-1; i>0; i--){
            if(a[i] == 1){
                flag = true;
                break;
            }
        }

        if(!flag){
            cout<<n-a[m-1]+1<<endl;
        }else{
            cout<<1<<endl;
        }
    }
    return 0;
}