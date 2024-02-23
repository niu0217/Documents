/* ************************************************************************
> File Name:     LeetCode199.cpp
> Author:        niu0217
> Created Time:  三  2/21 15:26:56 2024
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
    vector<int> rightSideView(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<int> result;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        while(!nodeQueue.empty()) {
            int size = nodeQueue.size();
            for(int i = 0; i < size; i++) {
                TreeNode* node = nodeQueue.front();
                nodeQueue.pop();
                if(i == size - 1) {
                    result.push_back(node->val);
                }
                if(node->left) {
                    nodeQueue.push(node->left);
                }
                if(node->right) {
                    nodeQueue.push(node->right);
                }
            }
        }
        return result;
    }
};
