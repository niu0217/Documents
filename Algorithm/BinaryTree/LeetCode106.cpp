/* ************************************************************************
> File Name:     LeetCode106.cpp
> Author:        niu0217
> Created Time:  五  2/23 17:44:24 2024
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
    TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
        //空节点处理
        if(postorder.size() == 0) {
            return nullptr;
        }
        //构建根结点
        int rootValue = postorder[postorder.size() - 1];
        TreeNode* root = new TreeNode(rootValue);
        //叶子节点处理
        if(postorder.size() == 1) {
            return root;
        }
        //找到分割点
        int delimiterIndex;
        for(delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex++) {
            if(inorder[delimiterIndex] == rootValue) {
                break;
            }
        }
        //分割中序数组
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
        //分割后序数组
        //关键点：中序数组长度一定和后序数组长度相同
        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());
        //构建左右子树
        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder, rightPostorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        //inorder和postorder中至少有一个为空
        if(inorder.size() == 0 || postorder.size() == 0) {
            return nullptr;
        }
        //inorder和postorderd都不为空
        return traversal(inorder, postorder);
    }
};
