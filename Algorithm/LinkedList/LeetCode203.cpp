/* ************************************************************************
> File Name:     LeetCode203.cpp
> Author:        niu0217
> Created Time:  四  2/15 16:05:47 2024
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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* curNode = dummyHead;
        while(curNode->next != nullptr) {
            if(curNode->next->val == val) {
                ListNode* toDeleteNode = curNode->next;
                curNode->next = toDeleteNode->next;
                delete toDeleteNode;
                toDeleteNode = nullptr;
            }
            else {
                curNode = curNode->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        dummyHead = nullptr;
        return head;
    }
};
