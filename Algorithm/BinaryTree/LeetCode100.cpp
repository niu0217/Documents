/* ************************************************************************
> File Name:     LeetCode100.cpp
> Author:        niu0217
> Created Time:  三  2/21 17:31:55 2024
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
    bool isSameTree(TreeNode* rootA, TreeNode* rootB) {
        //剪枝
        if(rootA == nullptr && rootB != nullptr) {
            return false;
        }
        if(rootA != nullptr && rootB == nullptr) {
            return false;
        }
        if(rootA == nullptr && rootB == nullptr) {
            return true;
        }
        //rootA：中左右
        //rootB：中左右
        bool condition1 = rootA->val == rootB->val;
        bool condition2 = isSameTree(rootA->left, rootB->left);
        bool condition3 = isSameTree(rootA->right, rootB->right);
        return condition1 && condition2 && condition3;
    }
};
