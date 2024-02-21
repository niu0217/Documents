/* ************************************************************************
> File Name:     LeetCode94.cpp
> Author:        niu0217
> Created Time:  三  2/21 13:31:24 2024
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
    void midorder(TreeNode* root, vector<int>& result) {
        if(root == nullptr) {
            return;
        }
        midorder(root->left, result);
        result.push_back(root->val);
        midorder(root->right, result);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        midorder(root, result);
        return result;
    }
};
