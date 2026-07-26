// Longest Substring without Repeating Characters
// Given a string s, find the length of the longest substring without duplicate characters.
// Example 1:
// Input: s = "abcabcbb"
// i=0 r=4
// Output: 3
// Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
// Example 2:
// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
// Example 3:
// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.



//
#include<bits/stdc++.h>
using namespace std;


int lsr(string s){
    unordered_set<char> st;
    

    int l = 0;
    int ans = 0;
    for(int r=0; r<s.size(); r++){
        
        
        while(st.count(s[r])){
            st.erase(s[l]);
            l++;
        }
        st.insert(s[r]);

        ans = max(ans, r - l + 1);
    }
    return ans;
}

int main(){
    string s = "bbbbb";

    cout<<lsr(s);
    return 0;
}