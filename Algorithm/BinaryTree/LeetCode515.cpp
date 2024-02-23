/* ************************************************************************
> File Name:     LeetCode515.cpp
> Author:        niu0217
> Created Time:  三  2/21 15:42:13 2024
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
    vector<int> largestValues(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<int> result;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        while(!nodeQueue.empty()) {
            int size = nodeQueue.size();
            int maxValue = INT_MIN;
            for(int i = 0; i < size; i++) {
                TreeNode* node = nodeQueue.front();
                nodeQueue.pop();
                maxValue = maxValue > node->val ? maxValue : node->val;
                if(node->left) {
                    nodeQueue.push(node->left);
                }
                if(node->right) {
                    nodeQueue.push(node->right);
                }
            }
            result.push_back(maxValue);
        }
        return result;
    }
};
