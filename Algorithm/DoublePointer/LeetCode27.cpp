/* ************************************************************************
> File Name:     LeetCode27.cpp
> Author:        niu0217
> Created Time:  日  2/18 13:18:33 2024
 ************************************************************************/

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //slow:  需要修改的位置
        //fast:  下一个不等于val的位置
        int slow = 0; 
        for(int fast = 0; fast < nums.size(); fast++) {
            if(nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
