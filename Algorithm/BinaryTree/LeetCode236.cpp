/* ************************************************************************
> File Name:     LeetCode236.cpp
> Author:        niu0217
> Created Time:  六  2/24 14:29:05 2024
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
    //大前提
    // p!=q
    // p和q一定存在当前树中
    // 结点值各不相同
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root == q || root == nullptr) {
            return root;
        }
        //leftSubtree为空表示左子树中没有p也没有q，不为空表示左子树中有p或者有q
        //rightSubtree为空表示右子树中没有p也没有q，不为空表示右子树中有p或者有q
        TreeNode* leftSubtree = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightSubtree = lowestCommonAncestor(root->right, p, q);
        if(leftSubtree != nullptr && rightSubtree != nullptr) {
            return root;
        }
        if(leftSubtree != nullptr && rightSubtree == nullptr) {
            return leftSubtree;
        }
        if(leftSubtree == nullptr && rightSubtree != nullptr) {
            return rightSubtree;
        }
        return nullptr;
    }
};
