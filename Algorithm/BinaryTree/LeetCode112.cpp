/* ************************************************************************
> File Name:     LeetCode112.cpp
> Author:        niu0217
> Created Time:  三  2/21 20:57:13 2024
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) {
            return false;
        }
        stack<int> sumStack;
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        sumStack.push(root->val);
        while(!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();
            int sum = sumStack.top();
            sumStack.pop();
            if(sum == targetSum && node->left == nullptr && node->right == nullptr) {
                return true;
            }
            if(node->right) {
                nodeStack.push(node->right);
                sumStack.push(sum + node->right->val);
            }
            if(node->left) {
                nodeStack.push(node->left);
                sumStack.push(sum + node->left->val);
            }
        }
        return false;
    }
};

//递归
class Solution {
public:
    bool traversal(TreeNode* root, int sum) {
        if(sum == 0 && root->left == nullptr && root->right == nullptr) {
            return true;
        }
        if(root->left == nullptr & root->right == nullptr) {
            return false;
        }
        if(root->left) {
            sum -= root->left->val;
            if(traversal(root->left, sum)) {
                return true;
            }
            sum += root->left->val;
        }
        if(root->right) {
            sum -= root->right->val;
            if(traversal(root->right, sum)) {
                return true;
            }
            sum += root->right->val;
        }
        return false;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) {
            return false;
        }
        int sum = targetSum - root->val;
        return traversal(root, sum);
    }
};
