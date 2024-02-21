/* ************************************************************************
> File Name:     LeetCode110.cpp
> Author:        niu0217
> Created Time:  三  2/21 19:16:04 2024
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
    int getHeight(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        int leftSubTreeHeight = getHeight(root->left);
        int rightSubTreeHeight = getHeight(root->right);
        return 1 + max(leftSubTreeHeight, rightSubTreeHeight);
    }
    bool isBalanced(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        bool condition1 = abs(getHeight(root->left) - getHeight(root->right)) <= 1;
        bool condition2 = isBalanced(root->left);
        bool condition3 = isBalanced(root->right);
        return condition1 && condition2 && condition3;
    }
};
