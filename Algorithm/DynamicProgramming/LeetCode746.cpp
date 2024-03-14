/* ************************************************************************
> File Name:     LeetCode746.cpp
> Author:        niu0217
> Created Time:  四  3/14 18:37:18 2024
 ************************************************************************/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        //dp[i]: 爬到第i个台阶时的最小花费
        //dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        //初始化
        //遍历顺序：从前往后
        int n = cost.size();
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 0;
        for(int i = 2; i <= n; i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[n];
    }
};
