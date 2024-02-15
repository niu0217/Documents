/* ************************************************************************
> File Name:     LeetCode707.cpp
> Author:        niu0217
> Created Time:  四  2/15 17:15:44 2024
 ************************************************************************/

class MyLinkedList {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val{0}, next{nullptr} { }
        ListNode(int x) : val{x}, next{nullptr} { }
        ListNode(int x, ListNode* next) : val{x}, next{next} { }
    };
private:
    ListNode* dummyHead;
    int linkelistSize;
public:
    MyLinkedList() {
        dummyHead = new ListNode(0);
        linkelistSize = 0;
    }

    int get(int index) {
        if(index >= linkelistSize || index < 0) {
            return -1;
        }
        ListNode* curNode = dummyHead->next;
        while(index--) {
            curNode = curNode->next;
        }
        return curNode->val;
    }

    void addAtHead(int val) {
        ListNode* toInsertNode = new ListNode(val);
        toInsertNode->next = dummyHead->next;
        dummyHead->next = toInsertNode;
        linkelistSize++;
    }

    void addAtTail(int val) {
        ListNode* toInsertNode = new ListNode(val);
        ListNode* curNode = dummyHead;
        while(curNode->next != nullptr) {
            curNode = curNode->next;
        }
        curNode->next = toInsertNode;
        linkelistSize++;
    }

    void addAtIndex(int index, int val) {
        if(index > linkelistSize) {
            return;
        }
        if(index < 0) {
            index = 0;
        }
        ListNode* toInsertNode = new ListNode(val);
        ListNode* curNode = dummyHead;
        while(index--) {
            curNode = curNode->next;
        }
        toInsertNode->next = curNode->next;
        curNode->next = toInsertNode;
        linkelistSize++;
    }

    void deleteAtIndex(int index) {
       if(index >= linkelistSize || index < 0) {
           return;
       }
       ListNode* curNode = dummyHead;
       while(index--) {
           curNode = curNode->next;
       }
       ListNode* toDeleteNode = curNode->next;
       curNode->next = toDeleteNode->next;
       delete toDeleteNode;
       toDeleteNode = nullptr;
       linkelistSize--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
