/* ************************************************************************
> File Name:     LeetCode322.cpp
> Author:        niu0217
> Created Time:  四  3/21 21:37:10 2024
 ************************************************************************/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < coins.size(); i++) {
            for(int j = coins[i]; j <= amount; j++) {
                if(dp[j - coins[i]] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
                }
            }
        }
        if(dp[amount] == INT_MAX) {
            return -1;
        }
        return dp[amount];
    }
};
