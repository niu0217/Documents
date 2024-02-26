/* ************************************************************************
> File Name:     LeetCode78.cpp
> Author:        niu0217
> Created Time:  一  2/26 20:08:44 2024
 ************************************************************************/

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
public:
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        if(startIndex >= nums.size()) {
            return;
        }
        for(int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
