/* ************************************************************************
> File Name:     LeetCode654.cpp
> Author:        niu0217
> Created Time:  五  2/23 22:13:37 2024
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
    int findMaxIndex(vector<int>& nums) {
        auto maxIt = max_element(nums.begin(), nums.end());
        return distance(nums.begin(), maxIt);
    }
    TreeNode* traversal(vector<int>& nums) {
        if(nums.size() == 0) {
            return nullptr;
        }
        //构建根结点
        int idxMax = findMaxIndex(nums);
        int rootValue = nums[idxMax];
        TreeNode* root = new TreeNode(rootValue);
        //叶子节点
        if(nums.size() == 1) {
            return root;
        }
        //分割为两部分
        vector<int> leftPart(nums.begin(), nums.begin() + idxMax);
        vector<int> rightPart(nums.begin() + idxMax + 1, nums.end());
        //构建左右子树
        root->left = traversal(leftPart);
        root->right = traversal(rightPart);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.size() == 0) {
            return nullptr;
        }
        return traversal(nums);
    }
};
