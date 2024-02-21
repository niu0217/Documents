/* ************************************************************************
> File Name:     LeetCode116.cpp
> Author:        niu0217
> Created Time:  三  2/21 15:47:12 2024
 ************************************************************************/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root == nullptr) {
            return nullptr;
        }
        queue<Node*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            Node* preNode = nullptr;
            for(int i = 0; i < size; i++) {
                Node* curNode = que.front();
                que.pop();
                if(preNode != nullptr) {
                    preNode->next = curNode;
                }
                preNode = curNode;
                if(curNode->left) {
                    que.push(curNode->left);
                }
                if(curNode->right) {
                    que.push(curNode->right);
                }
            }
        }
        return root;
    }
};