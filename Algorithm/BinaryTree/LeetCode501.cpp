/* ************************************************************************
> File Name:     LeetCode501.cpp
> Author:        niu0217
> Created Time:  六  2/24 13:06:11 2024
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
    bool static compare(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
    void traversal(TreeNode* root, unordered_map<int, int>& umap) {
        if(root == nullptr) {
            return;
        }
        umap[root->val]++;
        traversal(root->left, umap);
        traversal(root->right, umap);
    }
    vector<int> findMode(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        //key:   元素
        //value: 元素出现的次数
        unordered_map<int, int> umap;
        traversal(root, umap);
        vector<int> result;
        vector<pair<int, int>> vec(umap.begin(), umap.end());
        //按照频率排序
        sort(vec.begin(), vec.end(), compare);
        result.push_back(vec[0].first);
        for(int i = 1; i < vec.size(); i++) {
            if(vec[i].second == vec[0].second) {
                result.push_back(vec[i].first);
            }
        }
        return result;
    }
};

//中序遍历  递归
class Solution {
public:
    vector<int> result;
    TreeNode* preNode = nullptr;
    int maxCount = 0;
    int count = 0;
    void traversal(TreeNode* curNode) {
        if(curNode == nullptr) {
            return;
        }
        traversal(curNode->left);
        if(preNode == nullptr) {
            count = 1;
        }
        else {
            if(preNode->val == curNode->val) {
                count++;
            }
            else {
                count = 1;
            }
        }
        preNode = curNode;
        if(count == maxCount) {
            result.push_back(curNode->val);
        }
        if(count > maxCount) {
            maxCount = count;
            result.clear();
            result.push_back(curNode->val);
        }
        traversal(curNode->right);
    }
    vector<int> findMode(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        result.clear();
        traversal(root);
        return result;
    }
};

//中序遍历  迭代
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        if(root == nullptr) {
            return {};
        }
        int maxCount = 0;
        int count = 0;
        vector<int> result;
        TreeNode* preNode = nullptr;
        TreeNode* curNode = root;
        stack<TreeNode*> nodeStack;
        while(!nodeStack.empty() || curNode != nullptr) {
            if(curNode != nullptr) {
                nodeStack.push(curNode);
                curNode = curNode->left;
            }
            else {
                curNode = nodeStack.top();
                nodeStack.pop();
                if(preNode == nullptr) {
                    count = 1;
                }
                else if(preNode->val == curNode->val) {
                    count++;
                }
                else {
                    count = 1;
                }
                preNode = curNode;
                if(count == maxCount) {
                    result.push_back(curNode->val);
                }
                if(count > maxCount) {
                    maxCount = count;
                    result.clear();
                    result.push_back(curNode->val);
                }
                curNode = curNode->right;
            }
        }
        return result;
    }
};
