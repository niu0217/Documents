/* ************************************************************************
> File Name:     LeetCode530.cpp
> Author:        niu0217
> Created Time:  六  2/24 12:29:22 2024
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
    void traversal(TreeNode* root, vector<int>& result) {
        if(root == nullptr) {
            return;
        }
        traversal(root->left, result);
        result.push_back(root->val);
        traversal(root->right, result);
    }
    int getMinimumDifference(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        vector<int> result;
        traversal(root, result);
        int minimumDifference = INT_MAX;
        for(int i = 1; i < result.size(); i++) {
            minimumDifference = min(result[i] - result[i - 1], minimumDifference);
        }
        return minimumDifference;
    }
};

class Solution {
public:
    int result = INT_MAX;
    TreeNode* preNode = nullptr;
    void traversal(TreeNode* curNode) {
        if(curNode == nullptr) {
            return;
        }
        traversal(curNode->left);
        if(preNode != nullptr) {
            result = min(result, curNode->val - preNode->val);
        }
        preNode = curNode;
        traversal(curNode->right);
    }
    int getMinimumDifference(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        traversal(root);
        return result;
    }
};
