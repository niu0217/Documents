/* ************************************************************************
> File Name:     LeetCode19.cpp
> Author:        niu0217
> Created Time:  四  2/15 19:22:15 2024
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* slowNode = dummyHead;
        ListNode* fastNode = dummyHead;
        while(n--) {
            fastNode = fastNode->next;
        }
        while(fastNode->next != nullptr) {
            slowNode = slowNode->next;
            fastNode = fastNode->next;
        }
        ListNode* toDeleteNode = slowNode->next;
        slowNode->next = toDeleteNode->next;
        delete toDeleteNode;
        toDeleteNode = nullptr;
        head = dummyHead->next;
        delete dummyHead;
        dummyHead = nullptr;
        return head;
    }
};
