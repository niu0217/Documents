/* ************************************************************************
> File Name:     LeetCode15.cpp
> Author:        niu0217
> Created Time:  日  2/18 14:09:13 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i++) {
            //剪枝
            if(nums[i] > 0) {
                break;
            }
            //对nums[i]去重
            if(i > 0 && nums[i] == nums[i -1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while(left < right) {
                if(nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                }
                else if(nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                }
                else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    //对left和right去重
                    while(left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    while(left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    //同时收缩双指针
                    left++;
                    right--;
                }
            }
        }
        return result;
    }
};
