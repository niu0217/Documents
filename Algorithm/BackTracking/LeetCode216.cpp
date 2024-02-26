/* ************************************************************************
> File Name:     LeetCode216.cpp
> Author:        niu0217
> Created Time:  一  2/26 13:21:47 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int k, int n, int startIndex, int sum) {
        if(sum > n) {
            return;
        }
        if(k == path.size() && sum == n) {
            result.push_back(path);
            return;
        }
        for(int i = startIndex; i <= 9; i++) {
            sum += i;
            path.push_back(i);
            backtracking(k, n, i + 1, sum);
            path.pop_back();
            sum -= i;
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear();
        path.clear();
        backtracking(k, n, 1, 0);
        return result;
    }
};

class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int k, int n, int startIndex, int sum) {
        //剪枝
        if(sum > n) {
            return;
        }
        if(path.size() == k) {
            if(sum == n) {
                result.push_back(path);
            }
            return;
        }
        for(int i = startIndex; i <= 9; i++) {
            sum += i;
            path.push_back(i);
            backtracking(k, n, i + 1, sum);
            path.pop_back();
            sum -= i;
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear();
        path.clear();
        backtracking(k, n, 1, 0);
        return result;
    }
};
