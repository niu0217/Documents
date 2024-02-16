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
    int getListSize(ListNode* head) {
        ListNode* curNode = head;
        int listSize = 0;
        while(curNode != nullptr) {
            curNode = curNode->next;
            ++listSize;
        }
        return listSize;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int aListSize = getListSize(headA);
        int bListSize = getListSize(headB);
        ListNode* curANode = headA;
        ListNode* curBNode = headB;
        //保持curANode始终指向最长的那条链表
        if(aListSize < bListSize) {
            swap(aListSize, bListSize);
            swap(curANode, curBNode);
        }
        int gap = aListSize - bListSize;
        while(gap--) {
            curANode = curANode->next;
        }
        while(curANode != nullptr) {
            if(curANode == curBNode) {
                return curANode;
            }
            curANode = curANode->next;
            curBNode = curBNode->next;
        }
        return nullptr;
    }
};
