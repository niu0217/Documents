/* ************************************************************************
> File Name:     LeetCode206.cpp
> Author:        niu0217
> Created Time:  日  2/18 13:46:16 2024
 ************************************************************************/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* preNode = nullptr;
        ListNode* curNode = head;
        ListNode* nextNode = nullptr;
        while(curNode != nullptr) {
            nextNode = curNode->next;
            curNode->next = preNode;
            preNode = curNode;
            curNode = nextNode;
        }
        return preNode;
    }
};
