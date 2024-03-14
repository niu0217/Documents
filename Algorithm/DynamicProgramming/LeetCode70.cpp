/* ************************************************************************
> File Name:     LeetCode70.cpp
> Author:        niu0217
> Created Time:  四  3/14 18:11:46 2024
 ************************************************************************/

class Solution {
public:
    int climbStairs(int n) {
        //第三层楼梯的状态可以由第二层楼梯和到第一层楼梯状态推导出来
        //dp[i]： 爬到第i层楼梯，有dp[i]种方法
        //dp[i] = dp[i - 1] + dp[i - 2];
        //遍历顺序：从前往后
        if(n == 1) {
            return 1;
        }
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
