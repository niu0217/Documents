/* ************************************************************************
> File Name:     LeetCode160.cpp
> Author:        niu0217
> Created Time:  四  2/15 19:57:53 2024
 ************************************************************************/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    int getLinkedListLength(ListNode* head) {
        int linkedlistLength = 0;
        ListNode* curNode = head;
        while(curNode != nullptr) {
            linkedlistLength++;
            curNode = curNode->next;
        }
        return linkedlistLength;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int linkedlistALength = getLinkedListLength(headA);
        int linkedlistBLength = getLinkedListLength(headB);
        ListNode* curNodeA = headA;
        ListNode* curNodeB = headB;
        //让链表A始终是最长的一个链表
        while(linkedlistALength < linkedlistBLength) {
            swap(linkedlistALength, linkedlistBLength);
            swap(curNodeA, curNodeB);
        }
        int gap = linkedlistALength - linkedlistBLength;
        while(gap--) {
            curNodeA = curNodeA->next;
        }
        while(curNodeA != nullptr) {
            if(curNodeA == curNodeB) {
                return curNodeA;
            }
            curNodeA = curNodeA->next;
            curNodeB = curNodeB->next;
        }
        return nullptr;
    }
};
