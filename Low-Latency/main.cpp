// Valid Parentheses
// Given a string s containing only the characters '(', ')', '{', '}', '[', and ']', determine whether the input string is valid.
// An input string is valid if:
// Open brackets are closed by the same type of bracket.
// Open brackets are closed in the correct order.
// Every closing bracket has a corresponding opening bracket of the same type.
// Example 1:
// Input: s = "()"

// Output: true
// Example 2:
// Input: s = "()[]{}"

// Output: true
// Example 3:
// Input: s = "(]"

// Output: false
// Example 4:
// Input: s = "([])"

// Output: true
// Example 5:
// Input: s = "([)]"

// Output: false
#include<bits/stdc++.h>
using namespace std;

bool isVaild(string s){
    stack<char> st;

    for(char c: s){
        if(c == '(' || c== '{' || c== '['){
            st.push(c);
        }else{
            if(st.empty()) return false;

            if((c==')' && st.top() != '(') || (c=='}' && st.top() != '{') || (c==']' && st.top() != '[')){
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int main(){
    string s = "([])";

    cout<<isVaild(s);

    return 0;
}