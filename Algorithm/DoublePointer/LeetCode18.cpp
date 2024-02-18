/* ************************************************************************
> File Name:     LeetCode18.cpp
> Author:        niu0217
> Created Time:  日  2/18 14:09:44 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for(int k = 0; k < nums.size(); k++) {
            //剪枝
            if(nums[k] > target && nums[k] >= 0) {
                break;
            }
            //对nums[k]去重
            if(k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for(int i = k + 1; i < nums.size(); i++) {
                //二次剪枝
                if(nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) {
                    break;
                }
                //对nums[i]去重
                if(i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while(left < right) {
                    if((long)nums[k] + nums[i] + nums[left] + nums[right] > target) {
                        right--;
                    }
                    else if((long)nums[k] + nums[i] + nums[left] + nums[right] < target) {
                        left++;
                    }
                    else {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        //对left和right去重
                        while(left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        while(left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        //收缩双指针
                        left++;
                        right--;
                    }
                }
            }
        }
        return result;
    }
};
