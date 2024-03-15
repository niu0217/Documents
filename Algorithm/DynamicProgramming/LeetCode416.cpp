/* ************************************************************************
> File Name:     LeetCode416.cpp
> Author:        niu0217
> Created Time:  五  3/15 14:02:32 2024
 ************************************************************************/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(); //物品的个数
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % 2 == 1) {
            return false;
        }
        int m = sum / 2; //背包的容量
        vector<vector<int>> dp(n, vector<int>(m + 1, 0));
        for(int j = 1; j <= m; j++) {
            dp[0][j] = nums[0];
        }
        for(int i = 1; i < n; i++) {
            for(int j = 1; j <= m; j++) {
                if(j < nums[i]) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - nums[i]] + nums[i]);
                }
                if(dp[i][j] == m) {
                    return true;
                }
            }
        }
        return false;
    }
};
