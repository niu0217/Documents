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
        //leftSubTree告诉我们左子树中是否出现过p或者q，如果没出现，则值应该是nullptr
        //rightSubTree告诉我们右子树中是否出现过p或者q，如果没出现，则值应该是nullptr
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
            //leftSubTree == nullptr && rightSubTree == nullptr
            return nullptr;
        }
        return nullptr;
    }
};
