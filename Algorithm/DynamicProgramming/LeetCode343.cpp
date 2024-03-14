/* ************************************************************************
> File Name:     LeetCode343.cpp
> Author:        niu0217
> Created Time:  四  3/14 20:33:12 2024
 ************************************************************************/

class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for(int i = 3; i <= n; i++) {
            for(int j = 1; j <= i / 2; j++) {
                dp[i] = max(dp[i], max(dp[i - j] * j, (i - j) * j));
            }
        }
        return dp[n];
    }
};
