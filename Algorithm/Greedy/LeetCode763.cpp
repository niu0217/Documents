/* ************************************************************************
> File Name:     LeetCode763.cpp
> Author:        niu0217
> Created Time:  四  2/29 14:43:25 2024
 ************************************************************************/

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int hash[27] = {0};
        //记录每个字母最远出现的下标
        for(int i = 0; i < s.size(); i++) {
            hash[s[i] - 'a'] = i;
        }
        int left = 0;
        int right = 0;
        vector<int> result;
        for(int i = 0; i < s.size(); i++) {
            right = max(right, hash[s[i] - 'a']);
            if(i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        return result;
    }
};
