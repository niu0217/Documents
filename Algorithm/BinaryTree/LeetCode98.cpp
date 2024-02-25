/* ************************************************************************
> File Name:     LeetCode98.cpp
> Author:        niu0217
> Created Time:  六  2/24 11:20:13 2024
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
//错误解法
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        if(root->left == nullptr && root->right == nullptr) {
            return true;
        }
        if(root->left != nullptr && root->right == nullptr) {
            if(root->left->val < root->val) {
                return isValidBST(root->left);
            }
            return false;
        }
        if(root->left == nullptr && root->right != nullptr) {
            if(root->right->val > root->val) {
                return isValidBST(root->right);
            }
            return false;
        }
        //到这里root->left和root->right都不为空
        bool condition1 = root->left->val < root->val;
        bool condition2 = root->right->val > root->val;
        bool condition3 = isValidBST(root->left);
        bool condition4 = isValidBST(root->right);
        return condition1 && condition2 && condition3 && condition4;
    }
};

//关键点：中序遍历的数组是有序的
class Solution {
public:
    void traversal(TreeNode* root, vector<int>& nums) {
        if(root == nullptr) {
            return;
        }
        traversal(root->left, nums);
        nums.push_back(root->val);
        traversal(root->right, nums);
    }
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        vector<int> nums;
        traversal(root, nums);
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] <= nums[i - 1]) {
                return false;
            }
        }
        return true;
    }
};

//递归
class Solution {
public:
    TreeNode* preNode = nullptr;
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        bool condition1 = isValidBST(root->left);
        if(preNode != nullptr) {
            if(preNode->val >= root->val) {
                return false;
            }
        }
        preNode = root;
        bool condition2 = isValidBST(root->right);
        return condition1 && condition2;
    }
};
