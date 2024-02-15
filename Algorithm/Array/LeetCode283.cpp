/* ************************************************************************
> File Name:     LeetCode283.cpp
> Author:        niu0217
> Created Time:  二  2/13 10:15:33 2024
 ************************************************************************/

//双指针法
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        //slowIndex: 需要修改的位置
        //fastIndex: 下一个不等于0的位置
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if(nums[fastIndex] != 0) {
                swap(nums[slowIndex], nums[fastIndex]);
                slowIndex++;
            }
        }
    }
};
