/* ************************************************************************
> File Name:     LeetCode47.cpp
> Author:        niu0217
> Created Time:  二  2/27 14:19:47 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, vector<bool>& used) {
        if(path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for(int i = 0; i < nums.size(); i++) {
            if(used[i] == true) {
                continue;
            }
            if(i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
