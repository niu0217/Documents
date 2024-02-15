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
        int sumOfCurWindow = 0;
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            sumOfCurWindow += nums[fastIndex];
            while(sumOfCurWindow >= target) {
                int curWindowSize = fastIndex - slowIndex + 1;
                minLength = minLength > curWindowSize ? curWindowSize : minLength;
                sumOfCurWindow -= nums[slowIndex];
                slowIndex++;
            }
        }
        return minLength == INT_MAX ? 0 : minLength;
    }
};
