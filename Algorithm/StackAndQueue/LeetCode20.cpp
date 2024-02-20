/* ************************************************************************
> File Name:     LeetCode20.cpp
> Author:        niu0217
> Created Time:  二  2/20 13:25:24 2024
 ************************************************************************/

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char ch : s) {
            if(!st.empty() && st.top() == ch) {
                st.pop();
            }
            else if(ch == '(') {
                st.push(')');
            }
            else if(ch == '{') {
                st.push('}');
            }
            else if(ch == '[') {
                st.push(']');
            }
            else {
                return false;
            }
        }
        return st.empty();
    }
};
