/* ************************************************************************
> File Name:     LeetCode669.cpp
> Author:        niu0217
> Created Time:  六  2/24 16:14:58 2024
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
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root == nullptr) {
            return nullptr;
        }
        if(root->val < low) {
            TreeNode* rightPart = trimBST(root->right, low, high);
            return rightPart;
        }
        if(root->val > high) {
            TreeNode* leftPart = trimBST(root->left, low,high);
            return leftPart;
        }
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
};
