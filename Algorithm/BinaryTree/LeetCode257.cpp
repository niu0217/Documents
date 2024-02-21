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
        stack<TreeNode*> treenodeStack;
        stack<string> pathStack;
        vector<string> pathCollection;
        treenodeStack.push(root);
        pathStack.push(to_string(root->val));
        while(!treenodeStack.empty()) {
            TreeNode* node = treenodeStack.top();
            treenodeStack.pop();
            string path = pathStack.top();
            pathStack.pop();
            //是叶子节点，收割路径
            if(node->left == nullptr && node->right == nullptr) {
                pathCollection.push_back(path);
            }
            if(node->right) {
                treenodeStack.push(node->right);
                pathStack.push(path + "->" + to_string(node->right->val));
            }
            if(node->left) {
                treenodeStack.push(node->left);
                pathStack.push(path + "->" + to_string(node->left->val));
            }
        }
        return pathCollection;
    }
};

//递归
class Solution {
public:
    void traversal(TreeNode* root, vector<string>& result, string path) {
        //采用前序遍历，遇到叶子节点就收割
        path += to_string(root->val);
        if(root->left == nullptr && root->right == nullptr) {
            result.push_back(path);
            return;
        }
        if(root->left) {
            path += "->";
            traversal(root->left, result, path);
            path.pop_back(); //回溯">"
            path.pop_back(); //回溯"-"
        }
        if(root->right) {
            path += "->";
            traversal(root->right, result, path);
            path.pop_back(); //回溯">"
            path.pop_back(); //回溯"-"
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        vector<string> result;
        string path;
        traversal(root, result, path);
        return result;
    }
};
