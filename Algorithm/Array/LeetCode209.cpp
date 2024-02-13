/* ************************************************************************
> File Name:     LeetCode209.cpp
> Author:        niu0217
> Created Time:  二  2/13 11:35:44 2024
 ************************************************************************/

//双指针法
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minLength = INT_MAX;
        int slowIndex = 0;
        int sum = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            sum += nums[fastIndex];
            while(sum >= target) {
                int curLength = fastIndex - slowIndex + 1;
                minLength = minLength > curLength ? curLength : minLength;
                sum -= nums[slowIndex];
                slowIndex++;
            }
        }
        return minLength == INT_MAX ? 0 : minLength;
    }
};
