/* ************************************************************************
> File Name:     LeetCode108.cpp
> Author:        niu0217
> Created Time:  六  2/24 16:25:40 2024
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
    TreeNode* traversal(vector<int>& nums, int idxLeft, int idxRight) {
        if(idxLeft > idxRight) {
            return nullptr;
        }
        int idxMid = idxLeft + ((idxRight - idxLeft) / 2);
        TreeNode* root = new TreeNode(nums[idxMid]);
        root->left = traversal(nums, idxLeft, idxMid - 1);
        root->right = traversal(nums, idxMid + 1, idxRight);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.size() == 0) {
            return nullptr;
        }
        return traversal(nums, 0, nums.size() - 1);
    }
};
