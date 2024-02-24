/* ************************************************************************
> File Name:     LeetCode701.cpp
> Author:        niu0217
> Created Time:  六  2/24 15:00:01 2024
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) {
            TreeNode* toInsertNode = new TreeNode(val);
            return toInsertNode;
        }
        if(val < root->val) {
            root->left = insertIntoBST(root->left, val);
        }
        if(val > root->val) {
            root->right = insertIntoBST(root->right, val);
        }
        return root;
    }
};
