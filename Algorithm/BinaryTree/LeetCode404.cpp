/* ************************************************************************
> File Name:     LeetCode404.cpp
> Author:        niu0217
> Created Time:  三  2/21 20:28:40 2024
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
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        int sum = 0;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        while(!nodeQueue.empty()) {
            int size = nodeQueue.size();
            for(int i = 0; i < size; i++) {
                TreeNode* node = nodeQueue.front();
                nodeQueue.pop();
                if(node->left != nullptr && node->left->left == nullptr && node->left->right == nullptr) {
                    sum += node->left->val;
                }
                if(node->left) {
                    nodeQueue.push(node->left);
                }
                if(node->right) {
                    nodeQueue.push(node->right);
                }
            }
        }
        return sum;
    }
};

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        int sum = 0;
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        while(!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();
            if(node->left != nullptr && node->left->left == nullptr && node->left->right == nullptr) {
                sum += node->left->val;
            }
            if(node->right) {
                nodeStack.push(node->right);
            }
            if(node->left) {
                nodeStack.push(node->left);
            }
        }
        return sum;
    }
};
