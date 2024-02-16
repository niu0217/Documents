/* ************************************************************************
> File Name:     LeetCode1.cpp
> Author:        niu0217
> Created Time:  五  2/16 15:30:03 2024
 ************************************************************************/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //key:   元素
        //value: 元素在nums中的下标
        unordered_map<int, int> umapNums;
        for(int i = 0; i < nums.size(); i++) {
            auto iter = umapNums.find(target - nums[i]);
            if(iter != umapNums.end()) {
                return {i, iter->second};
            }
            umapNums[nums[i]] = i;
        }
        return {};
    }
};
