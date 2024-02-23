/* ************************************************************************
> File Name:     LeetCode113.cpp
> Author:        niu0217
> Created Time:  五  2/23 17:15:52 2024
 ************************************************************************/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void traversal(TreeNode* root, vector<vector<int>>& allPaths, vector<int> curPath, int sum) {
        if(sum == 0 && root->left == nullptr && root->right == nullptr) {
            allPaths.push_back(curPath);
            return;
        }
        if(root->left == nullptr && root->right == nullptr) {
            return;
        }
        if(root->left) {
            sum -= root->left->val;
            curPath.push_back(root->left->val);
            traversal(root->left, allPaths, curPath, sum);
            curPath.pop_back();
            sum += root->left->val;
        }
        if(root->right) {
            sum -= root->right->val;
            curPath.push_back(root->right->val);
            traversal(root->right, allPaths, curPath, sum);
            curPath.pop_back();
            sum += root->right->val;
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) {
            return {};
        }
        vector<vector<int>> allPaths;
        vector<int> curPath;
        int sum = targetSum - root->val;
        curPath.push_back(root->val);
        traversal(root, allPaths, curPath, sum);
        return allPaths;
    }
};
