/* ************************************************************************
> File Name:     LeetCode494.cpp
> Author:        niu0217
> Created Time:  五  3/15 16:34:13 2024
 ************************************************************************/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(abs(target) > sum) {
            return 0;
        }
        if((target + sum) % 2 == 1) {
            return 0;
        }
        int bagSize = (target + sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for(int i = 0; i < nums.size(); i++) {
            for(int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};
