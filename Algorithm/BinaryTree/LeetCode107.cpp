/* ************************************************************************
> File Name:     LeetCode107.cpp
> Author:        niu0217
> Created Time:  三  2/21 15:22:35 2024
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<vector<int>> result;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            vector<int> curLevelResult;
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                curLevelResult.push_back(node->val);
                if(node->left) {
                    que.push(node->left);
                }
                if(node->right) {
                    que.push(node->right);
                }
            }
            result.push_back(curLevelResult);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
