/* ************************************************************************
> File Name:     LeetCode1049.cpp
> Author:        niu0217
> Created Time:  五  3/15 14:42:00 2024
 ************************************************************************/

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size(); //物品个数
        int m = sum / 2; //背包容量
        vector<vector<int>> dp(n, vector<int>(m + 1, 0));
        for(int j = stones[0]; j <= m; j++) {
            dp[0][j] = stones[0];
        }
        for(int i = 1; i < n; i++) {
            for(int j = 1; j <= m; j++) {
                if(j < stones[i]) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stones[i]] + stones[i]);
                }
            }
        }
        return sum - dp[n - 1][m] - dp[n - 1][m];
    }
};

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size(); //物品个数
        int m = sum / 2; //背包容量
        vector<int> dp(m + 1, 0);
        for(int i = 0; i < n; i++) {
            for(int j = m; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[m] - dp[m];
    }
};
