/* ************************************************************************
> File Name:     LeetCode977.cpp
> Author:        niu0217
> Created Time:  二  2/13 11:20:47 2024
 ************************************************************************/

//双指针法
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int slowIndex = 0;
        int fastIndex = nums.size() - 1;
        int curIndex = nums.size() - 1;
        vector<int> result(nums.size());
        while(slowIndex <= fastIndex) {
            if(nums[slowIndex] * nums[slowIndex] < nums[fastIndex] * nums[fastIndex]) {
                result[curIndex--] = nums[fastIndex] * nums[fastIndex];
                fastIndex--;
            }
            else {
                result[curIndex--] = nums[slowIndex] * nums[slowIndex];
                slowIndex++;
            }
        }
        return result;
    }
};
