/* ************************************************************************
> File Name:     LeetCode283.cpp
> Author:        niu0217
> Created Time:  二  2/13 10:15:33 2024
 ************************************************************************/

//双指针法
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slowIndex = -1;
        int fastIndex = 0;
        int numsLength = nums.size();
        while(fastIndex < numsLength) {
            if(nums[fastIndex] != 0) {
                swap(nums[fastIndex], nums[slowIndex + 1]);
                slowIndex++;
                fastIndex++;
            }
            else {
                fastIndex++;
            }
        }
    }
};
