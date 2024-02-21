/* ************************************************************************
> File Name:     LeetCode429.cpp
> Author:        niu0217
> Created Time:  三  2/21 15:34:21 2024
 ************************************************************************/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(root == nullptr) {
            return {};
        }
        vector<vector<int>> result;
        queue<Node*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            vector<int> curLevelResult;
            for(int i = 0; i < size; i++) {
                Node* curNode = que.front();
                que.pop();
                curLevelResult.push_back(curNode->val);
                for(int j = 0; j < curNode->children.size(); j++) {
                    if(curNode->children[j] != nullptr) {
                        que.push(curNode->children[j]);
                    }
                }
            }
            result.push_back(curLevelResult);
        }
        return result;
    }
};
