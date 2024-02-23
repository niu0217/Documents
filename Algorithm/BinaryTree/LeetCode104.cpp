/* ************************************************************************
> File Name:     LeetCode104.cpp
> Author:        niu0217
> Created Time:  三  2/21 15:57:50 2024
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
    int maxDepth(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        int depth = 0;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        while(!nodeQueue.empty()) {
            int size = nodeQueue.size();
            depth++;
            for(int i = 0; i < size; i++) {
                TreeNode* node = nodeQueue.front();
                nodeQueue.pop();
                if(node->left) {
                    nodeQueue.push(node->left);
                }
                if(node->right) {
                    nodeQueue.push(node->right);
                }
            }
        }
        return depth;
    }
};

//递归
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        int leftSubTreeDepth = maxDepth(root->left);
        int rightSubTreeDepth = maxDepth(root->right);
        return 1 + max(leftSubTreeDepth, rightSubTreeDepth);
    }
};
