/* ************************************************************************
> File Name:     LeetCode160.cpp
> Author:        niu0217
> Created Time:  日  2/18 14:00:02 2024
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
        int listSize = 0;
        ListNode* curNode = head;
        while(curNode != nullptr) {
            listSize++;
            curNode = curNode->next;
        }
        return listSize;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int aListSize = getListSize(headA);
        int bListSize = getListSize(headB);
        ListNode* curANode = headA;
        ListNode* curBNode = headB;
        //让curANode始终指向最长的那条链表
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
