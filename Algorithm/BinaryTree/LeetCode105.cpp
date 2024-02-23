/* ************************************************************************
> File Name:     LeetCode105.cpp
> Author:        niu0217
> Created Time:  五  2/23 21:57:20 2024
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
    TreeNode* traversal(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0) {
            return nullptr;
        }
        //构建根结点
        int rootValue = preorder[0];
        TreeNode* root = new TreeNode(rootValue);
        //叶子节点
        if(preorder.size() == 1) {
            return root;
        }
        //寻找分割点
        int delimiterIndex;
        for(delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex++) {
            if(inorder[delimiterIndex] == rootValue) {
                break;
            }
        }
        //分割中序数组
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
        //分割前序数组
        preorder.erase(preorder.begin());
        vector<int> leftPreorder(preorder.begin(), preorder.begin() + leftInorder.size());
        vector<int> rightPreorder(preorder.begin() + leftInorder.size(), preorder.end());
        //构建左右子树
        root->left = traversal(leftPreorder, leftInorder);
        root->right = traversal(rightPreorder, rightInorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //preorder和inorder至少有一个为空
        if(preorder.size() == 0 || inorder.size() == 0) {
            return nullptr;
        }
        return traversal(preorder, inorder);
    }
};
