/* ************************************************************************
> File Name:     LeetCode279.cpp
> Author:        niu0217
> Created Time:  四  3/21 21:55:53 2024
 ************************************************************************/

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i * i <= n; i++) {
            for(int j = i * i; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - i * i] + 1);
            }
        }
        return dp[n];
    }
};
