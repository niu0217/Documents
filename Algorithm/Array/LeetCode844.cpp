/* ************************************************************************
> File Name:     LeetCode844.cpp
> Author:        niu0217
> Created Time:  二  2/13 10:39:29 2024
 ************************************************************************/

//栈
class Solution {
public:
    string buildString(string context) {
        string result = "";
        for(auto c : context) {
            if(c != '#') {
                result.push_back(c);
            }
            else if(!result.empty()) {
                result.pop_back();
            }
        }
        return result;
    }
    bool backspaceCompare(string s, string t) {
        return buildString(s) == buildString(t);
    }
};  
