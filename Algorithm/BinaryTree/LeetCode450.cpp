/* ************************************************************************
> File Name:     LeetCode450.cpp
> Author:        niu0217
> Created Time:  六  2/24 15:20:47 2024
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
    TreeNode* getMinValueNode(TreeNode* root) {
       if(root == nullptr) {
           return root;
       }
       while(root->left != nullptr) {
           root = root->left;
       }
       return root;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) {
            return root;
        }
        if(key < root->val) {
            root->left = deleteNode(root->left, key);
        }
        else if(key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        else {
            if(root->left == nullptr) {
                TreeNode* afterDeleteNode = root->right;
                delete root;
                root = nullptr;
                return afterDeleteNode;
            }
            else if(root->right == nullptr) {
                TreeNode* afterDeleteNode = root->left;
                delete root;
                root = nullptr;
                return afterDeleteNode;
            }
            else {
                //用右子树的最小值结点来代替
                TreeNode* minSubTreeNode = getMinValueNode(root->right);
                root->val = minSubTreeNode->val;
                root->right = deleteNode(root->right, minSubTreeNode->val);
            }
        }
        return root;
    }
};
