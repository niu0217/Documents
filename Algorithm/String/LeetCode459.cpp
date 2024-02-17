/* ************************************************************************
> File Name:     LeetCode459.cpp
> Author:        niu0217
> Created Time:  六  2/17 17:53:35 2024
 ************************************************************************/

class Solution {
public:
    void getPrefix(string s, vector<int>& prefix) {
        //j: 前缀的末尾
        //i: 后缀的末尾
        int j = 0;
        prefix[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while(j > 0 && s[i] != s[j]) {
                j = prefix[j - 1];
            }
            if(s[i] == s[j]) {
                j++;
            }
            prefix[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s) {
        vector<int> prefix(s.size(), 0);
        getPrefix(s, prefix);
        int len = s.size();
        if(prefix[len - 1] != 0 && len % (len - prefix[len - 1]) == 0) {
            return true;
        }
        return false;
    }
};
