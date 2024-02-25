/* ************************************************************************
> File Name:     LeetCode235.cpp
> Author:        niu0217
> Created Time:  六  2/24 14:38:50 2024
 ************************************************************************/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root == q || root == nullptr) {
            return root;
        }
        //leftSubTree表示左子树中是否存在p或者q，如果不存在，则值为nullptr
        //rightSubTree表示右子树中是否存在p或者q，如果不存在，则值为nullptr
        TreeNode* leftSubTree = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightSubTree = lowestCommonAncestor(root->right, p, q);
        if(leftSubTree != nullptr && rightSubTree != nullptr) {
            return root;
        }
        else if(leftSubTree != nullptr && rightSubTree == nullptr) {
            return leftSubTree;
        }
        else if(leftSubTree == nullptr && rightSubTree != nullptr) {
            return rightSubTree;
        }
        else {
            //leftSubTree == nullptr && rightSubTree == nullptr;
            return nullptr;
        }
        return nullptr;
    }
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root == q || root == nullptr) {
            return root;
        }
        if(p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        if(p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        return root;
    }
};
