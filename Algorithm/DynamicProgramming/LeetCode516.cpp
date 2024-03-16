/* ************************************************************************
> File Name:     LeetCode516.cpp
> Author:        niu0217
> Created Time:  六  3/16 11:41:48 2024
 ************************************************************************/

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        for(int i = 0; i < s.size(); i++) {
            dp[i][i] = 1;
        }
        for(int i = s.size() - 1; i >= 0; i--) {
            for(int j = i + 1; j < s.size(); j++) {
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
