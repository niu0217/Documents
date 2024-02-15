/* ************************************************************************
> File Name:     LeetCode24.cpp
> Author:        niu0217
> Created Time:  四  2/15 18:27:19 2024
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
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* curNode = dummyHead;
        while(curNode->next != nullptr && curNode->next->next != nullptr) {
            ListNode* curNeedExchangeEndNode = curNode->next;
            ListNode* nextNeedExchangeStartNode = curNode->next->next->next;

            curNode->next = curNode->next->next;
            curNode->next->next = curNeedExchangeEndNode;
            curNode->next->next->next = nextNeedExchangeStartNode;

            curNode = curNode->next->next;
        }
        return dummyHead->next;
    }
};
