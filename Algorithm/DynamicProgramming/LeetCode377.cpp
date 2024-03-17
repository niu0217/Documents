/* ************************************************************************
> File Name:     LeetCode377.cpp
> Author:        niu0217
> Created Time:  日  3/17 19:58:29 2024
 ************************************************************************/

//超出时间限制
class Solution {
public:
    int result = 0;
    void backtracking(vector<int>& nums, int sum, int target) {
        if(sum == target) {
            result++;
            return;
        }
        for(int i = 0; i < nums.size() && sum + nums[i] <= target; i++) {
            sum += nums[i];
            backtracking(nums, sum, target);
            sum -= nums[i];
        }
    }
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        backtracking(nums, 0, target);
        return result;
    }
};

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for(int j = 0; j <= target; j++) {
            for(int i = 0; i < nums.size(); i++) {
                if(j >= nums[i] && dp[j] < INT_MAX - dp[j - nums[i]]) {
                    dp[j] += dp[j - nums[i]];
                }
            }
        }
        return dp[target];
    }
};
