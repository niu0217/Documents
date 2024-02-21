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
        if(root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return 0;
        }
        queue<TreeNode*> que;
        que.push(root);
        int sum = 0;
        while(!que.empty()) {
            int size = que.size();
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if(node->left != nullptr && node->left->left == nullptr && node->left->right == nullptr) {
                    sum += node->left->val;
                }
                if(node->left) {
                    que.push(node->left);
                }
                if(node->right) {
                    que.push(node->right);
                }
            }
        }
        return sum;
    }
};
