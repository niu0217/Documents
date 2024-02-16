/* ************************************************************************
> File Name:     LeetCode15.cpp
> Author:        niu0217
> Created Time:  五  2/16 16:30:35 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(begin(nums), end(nums));
        // a = nums[i]
        // b = nums[j]
        // c = -(a + b)
        for(int i = 0; i < nums.size(); i++) {
            //排序后第一个元素大于0，则后续元素不可能相加等于0
            if(nums[i] > 0) {
                break;
            }
            //三元组元素a去重
            if(i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            unordered_set<int> uset;
            for(int j = i + 1; j < nums.size(); j++) {
                //三元组元素b去重
                if(j > i + 2 && nums[j] == nums[j - 1] && nums[j - 1] == nums[j - 2]) {
                    continue;
                }
                int c = 0 - (nums[i] + nums[j]);
                if(uset.find(c) != uset.end()) {
                    result.push_back({nums[i], nums[j], c});
                    //三元组元素c去重
                    uset.erase(c);
                }
                else {
                    uset.insert(nums[j]);
                }
            }
        }
        return result;
    }
};
