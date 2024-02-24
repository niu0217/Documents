/* ************************************************************************
> File Name:     LeetCode538.cpp
> Author:        niu0217
> Created Time:  六  2/24 13:39:27 2024
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
    int preValue = 0;
    void traversal(TreeNode* root) {
        if(root == nullptr) {
            return;
        }
        traversal(root->right);
        root->val += preValue;
        preValue = root->val;
        traversal(root->left);
    }
    TreeNode* convertBST(TreeNode* root) {
        if(root == nullptr) {
            return nullptr;
        }
        traversal(root);
        return root;
    }
};

//迭代
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if(root == nullptr) {
            return nullptr;
        }
        int preValue = 0;
        TreeNode* curNode = root;
        stack<TreeNode*> nodeStack;
        while(!nodeStack.empty() || curNode != nullptr) {
            if(curNode != nullptr) {
                nodeStack.push(curNode);
                curNode = curNode->right;
            }
            else {
                curNode = nodeStack.top();
                nodeStack.pop();
                curNode->val += preValue;
                preValue = curNode->val;
                curNode = curNode->left;
            }
        }
        return root;
    }
};
