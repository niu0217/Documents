/* ************************************************************************
> File Name:     LeetCode111.cpp
> Author:        niu0217
> Created Time:  三  2/21 16:12:15 2024
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

//递归
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        int leftSubTreeDepth = minDepth(root->left);
        int rightSubTreeDepth = minDepth(root->right);
        if(leftSubTreeDepth == 0 && rightSubTreeDepth != 0) {
            return 1 + rightSubTreeDepth;
        }
        if(leftSubTreeDepth != 0 && rightSubTreeDepth == 0) {
            return 1 + leftSubTreeDepth;
        }
        return 1 + min(leftSubTreeDepth, rightSubTreeDepth);
    }
};

//迭代
class Solution {
public:
    int minDepth(TreeNode* root) {
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
                if(node->left == nullptr && node->right == nullptr) {
                    return depth;
                }
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
