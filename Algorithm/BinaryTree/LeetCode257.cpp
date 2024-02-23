/* ************************************************************************
> File Name:     LeetCode257.cpp
> Author:        niu0217
> Created Time:  三  2/21 19:23:02 2024
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
    vector<string> binaryTreePaths(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<string> result;
        stack<TreeNode*> nodeStack;
        stack<string> pathStack;
        nodeStack.push(root);
        pathStack.push(to_string(root->val));
        while(!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();
            string path = pathStack.top();
            pathStack.pop();
            if(node->left == nullptr && node->right == nullptr) {
                result.push_back(path);
            }
            if(node->right) {
                nodeStack.push(node->right);
                pathStack.push(path + "->" + to_string(node->right->val));
            }
            if(node->left) {
                nodeStack.push(node->left);
                pathStack.push(path + "->" + to_string(node->left->val));
            }
        }
        return result;
    }
};

//递归
class Solution {
public:
    void collectionPaths(TreeNode* root, vector<string>& result, string path) {
        path += to_string(root->val);
        if(root->left == nullptr && root->right == nullptr) {
            result.push_back(path);
            return;
        }
        if(root->left) {
            path += "->";
            collectionPaths(root->left, result, path);
            path.pop_back(); //回溯 >
            path.pop_back(); //回溯 -
        }
        if(root->right) {
            path += "->";
            collectionPaths(root->right, result, path);
            path.pop_back(); //回溯 >
            path.pop_back(); //回溯 -
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<string> result;
        string path = "";
        collectionPaths(root, result, path);
        return result;
    }
};
