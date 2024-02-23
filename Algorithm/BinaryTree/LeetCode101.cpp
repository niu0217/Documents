/* ************************************************************************
> File Name:     LeetCode101.cpp
> Author:        niu0217
> Created Time:  三  2/21 17:31:01 2024
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
    bool isSame(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr && root2 != nullptr) {
            return false;
        }
        if(root1 != nullptr && root2 == nullptr) {
            return false;
        }
        if(root1 == nullptr && root2 == nullptr) {
            return true;
        }
        bool condition1 = root1->val == root2->val;
        bool condition2 = isSame(root1->left, root2->right);
        bool condition3 = isSame(root1->right, root2->left);
        return condition1 && condition2 && condition3;
    }
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        return isSame(root, root);
    }
};
