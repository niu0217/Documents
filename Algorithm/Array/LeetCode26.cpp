/* ************************************************************************
> File Name:     LeetCode26.cpp
> Author:        niu0217
> Created Time:  二  2/13 09:52:29 2024
 ************************************************************************/

//双指针法
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int length = nums.size();
        if(length == 1) {
            return length;
        }
        int slowIndex = 0;
        int fastIndex = 1;
        while(fastIndex < length) {
            if(nums[fastIndex] != nums[slowIndex]) {
                nums[++slowIndex] = nums[fastIndex];
            }
            fastIndex++;
        }
        return slowIndex + 1;
    }
};
