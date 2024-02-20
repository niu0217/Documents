/* ************************************************************************
> File Name:     LeetCode1047.cpp
> Author:        niu0217
> Created Time:  二  2/20 13:36:48 2024
 ************************************************************************/

//使用栈
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        for(char ch : s) {
            if(!st.empty() && ch == st.top()) {
                st.pop();
            }
            else {
                st.push(ch);
            }
        }
        string result = "";
        while(!st.empty()) {
            result += st.top();
            st.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

//使用字符串操作
class Solution {
public:
    string removeDuplicates(string s) {
        string result = "";
        for(int ch : s) {
            if(result.size() != 0 && result.back() == ch) {
                result.pop_back();
            }
            else {
                result.push_back(ch);
            }
        }
        return result;
    }
};
