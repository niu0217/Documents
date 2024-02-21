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
        //前序遍历
        if(root == nullptr) {
            return false;
        }
        stack<TreeNode*> st;
        stack<int> sumStack;
        st.push(root);
        sumStack.push(root->val);
        while(!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            int sum = sumStack.top();
            sumStack.pop();
            if(sum == targetSum && node->left == nullptr && node->right == nullptr) {
                return true;
            }
            if(node->right) {
                st.push(node->right);
                sumStack.push(sum + node->right->val);
            }
            if(node->left) {
                st.push(node->left);
                sumStack.push(sum + node->left->val);
            }
        }
        return false;
    }
};
