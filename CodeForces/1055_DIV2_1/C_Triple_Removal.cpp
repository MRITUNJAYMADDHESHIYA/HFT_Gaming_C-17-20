#include<bits/stdc++.h>
using namespace std;


//1.queries question
//2.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;

        vector<int> arr(n);
        for(auto &it: arr) cin>>it;

        vector<int> pref(n);
        pref[0] = arr[0];

        for(int i=1; i<n; i++){
            pref[i] = pref[i-1] + arr[i];
        }

        vector<int> dp(n,1);
        for(int i=1; i<n; i++){
            if(arr[i-1] != arr[i]){
                dp[i] += dp[i-1];
            }
        }

        while(q--){
            int l,r;
            cin>>l>>r;
            l--; r--;
            int len = (r-l+1);
            int sum = pref[r] - pref[l] + arr[l];
            if(len%3 != 0 || sum%3 != 0){
                cout<<"-1\n";
                continue;
            }

            int ans = len/3;
            if(l > r - dp[r]) ans++;
            cout<<ans<<"\n";
        }
    }
    return 0;
}