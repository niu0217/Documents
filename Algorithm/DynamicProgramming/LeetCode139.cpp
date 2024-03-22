/* ************************************************************************
> File Name:     LeetCode139.cpp
> Author:        niu0217
> Created Time:  五  3/22 22:32:39 2024
 ************************************************************************/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for(int j = 1; j <= s.size(); j++) { //遍历背包
            for(int i = 0; i < j; i++) { //遍历物品
                string word = s.substr(i, j - i);
                if(wordSet.find(word) != wordSet.end() && dp[i]) {
                    dp[j] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
