/* ************************************************************************
> File Name:     LeetCode26.cpp
> Author:        niu0217
> Created Time:  二  2/13 09:52:29 2024
 ************************************************************************/

//双指针法
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //slowIndex: 用来判断fastIndex和slowIndex位置的元素是否相同
        //++slowIndex: 需要被修改的位置
        //fastIndex: 下一个和slowIndex位置元素不相同的位置
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if(nums[slowIndex] != nums[fastIndex]) {
                nums[++slowIndex] = nums[fastIndex];
            }
        }
        return slowIndex + 1;
    }
};
