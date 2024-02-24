/* ************************************************************************
> File Name:     LeetCode700.cpp
> Author:        niu0217
> Created Time:  六  2/24 10:55:40 2024
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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) {
            return nullptr;
        }
        if(root->val == val) {
            return root;
        }
        TreeNode* result = nullptr;
        if(root->left) {
            result = searchBST(root->left, val);
            if(result != nullptr && result->val == val) {
                return result;
            }
        }
        if(root->right) {
            result = searchBST(root->right, val);
            if(result != nullptr && result->val == val) {
                return result;
            }
        }
        return nullptr;
    }
};

//迭代
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) {
            return nullptr;
        }
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        while(!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();
            if(node->val == val) {
                return node;
            }
            if(node->right) {
                nodeStack.push(node->right);
            }
            if(node->left) {
                nodeStack.push(node->left);
            }
        }
        return nullptr;
    }
};

//二分
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) {
            return nullptr;
        }
        if(root->val == val) {
            return root;
        }
        if(root->val < val) {
            if(root->right) {
                return searchBST(root->right, val);
            }
            return nullptr;
        }
        else if(root->val >val) {
            if(root->left) {
                return searchBST(root->left, val);
            }
            return nullptr;
        }
        return nullptr;
    }
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) {
            return nullptr;
        }
        if(val == root->val) {
            return root;
        }
        else if(val < root->val) {
            return searchBST(root->left, val);
        }
        else {
            return searchBST(root->right, val);
        }
        return nullptr;
    }
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while(root != nullptr) {
            if(val == root->val) {
                break;
            }
            else if(val < root->val) {
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
        return root;
    }
};
