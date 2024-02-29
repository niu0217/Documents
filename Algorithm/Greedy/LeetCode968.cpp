/* ************************************************************************
> File Name:     LeetCode968.cpp
> Author:        niu0217
> Created Time:  四  2/29 16:23:00 2024
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
    int result = 0;
    //0: 无覆盖
    //1: 放摄像头
    //2: 有覆盖
    int traversal(TreeNode* root) {
        if(root == nullptr) {
            return 2;
        }
        int leftStatus = traversal(root->left);
        int rightStatus = traversal(root->right);
        if(leftStatus == 0 || rightStatus == 0) {
            result++;
            return 1;
        }
        if(leftStatus == 1 || rightStatus == 1) {
            return 2;
        }
        if(leftStatus == 2 && rightStatus == 2) {
            return 0;
        }
        //永远走不到这里
        return -1;
    }
    int minCameraCover(TreeNode* root) {
        if(traversal(root) == 0) {
            result++;
        }
        return result;
    }
};
