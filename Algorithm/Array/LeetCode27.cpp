/* ************************************************************************
> File Name:     LeetCode27.cpp
> Author:        程序员niu0217
> Created Time:  二  2/13 09:38:55 2024
> Description:   
 ************************************************************************/

//暴力解法
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        for(int i = 0; i < size; i++) {
            if(nums[i] == val) {
                for(int j = i + 1; j < size; j++) {
                    nums[j - 1] = nums[j];
                }
                i--;
                size--;
            }
        }
        return size;
    }
};

//双指针法
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if(val != nums[fastIndex]) {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex;
    }
};
