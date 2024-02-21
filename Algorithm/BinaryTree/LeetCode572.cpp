/* ************************************************************************
> File Name:     LeetCode572.cpp
> Author:        niu0217
> Created Time:  三  2/21 17:38:40 2024
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
    bool isSame(TreeNode* rootA, TreeNode* rootB) {
        if(rootA == nullptr && rootB != nullptr) {
            return false;
        }
        if(rootA != nullptr && rootB == nullptr) {
            return false;
        }
        if(rootA == nullptr && rootB == nullptr) {
            return true;
        }
        bool condition1 = rootA->val == rootB->val;
        bool condition2 = isSame(rootA->left, rootB->left);
        bool condition3 = isSame(rootA->right, rootB->right);
        return condition1 && condition2 && condition3;
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root == nullptr && subRoot != nullptr) {
            return false;
        }
        if(root != nullptr && subRoot == nullptr) {
            return false;
        }
        if(root == nullptr && subRoot == nullptr) {
            return true;
        }
        if(isSame(root, subRoot)) {
            return true;
        }
        bool atLeftSubtree = isSubtree(root->left, subRoot);
        bool atRigthSubtree = isSubtree(root->right, subRoot);
        return atLeftSubtree || atRigthSubtree;
    }
};
