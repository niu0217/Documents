/* ************************************************************************
> File Name:     LeetCode39.cpp
> Author:        niu0217
> Created Time:  一  2/26 14:15:38 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
        if(sum >= target) {
            if(sum == target) {
                result.push_back(path);
            }
            return;
        }
        for(int i = startIndex; i < candidates.size(); i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum, i);
            path.pop_back();
            sum -= candidates[i];
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        path.clear();
        backtracking(candidates, target, 0, 0);
        return result;
    }
};

//剪枝
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
        if(sum == target) {
            result.push_back(path);
        }
        for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum, i);
            path.pop_back();
            sum -= candidates[i];
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        path.clear();
        sort(candidates.begin(), candidates.end()); //关键步骤
        backtracking(candidates, target, 0, 0);
        return result;
    }
};
