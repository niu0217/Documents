/* ************************************************************************
> File Name:     LeetCode77.cpp
> Author:        niu0217
> Created Time:  一  2/26 12:18:26 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> result;
    void backtracking(vector<int> path, int n, int k, int curIndex, int depth) {
        if(depth == k) {
            result.push_back(path);
            return;
        }
        //n: 树的宽度
        //k: 树的深度
        for(int i = curIndex; i <= n; i++) {
            path.push_back(i);
            backtracking(path, n, k, i + 1, depth + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<int> path;
        result.clear();
        backtracking(path, n, k, 1, 0);
        return result;
    }
};

//简化
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if(path.size() == k) {
            result.push_back(path);
            return;
        }
        //n: 树的宽度
        //k: 树的深度
        for(int i = startIndex; i <= n; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        result.clear();
        path.clear();
        backtracking(n, k, 1);
        return result;
    }
};

//剪枝
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if(path.size() == k) {
            result.push_back(path);
            return;
        }
        //n: 树的宽度
        //k: 树的深度
        //path.size(): 已经选择的元素个数
        //k - path.size(): 还需要选择的元素个数
        //n - (k - path.size()) + 1: 在集合n中至多需要从该起始位置开始遍历
        for(int i = startIndex; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        result.clear();
        path.clear();
        backtracking(n, k, 1);
        return result;
    }
};
