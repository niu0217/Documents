#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

struct ListNode {
    explicit ListNode(int initialData)
        : data{ initialData }, next{ nullptr } { }
    ~ListNode() {
        cout<<"Destructure   "<<data<<"  ...\n";
    }
    int data;
    ListNode* next;
};

ListNode* insertNode(ListNode* head, int value) {
    ListNode* dummyNode = new ListNode(0);
    dummyNode->next = head;
    ListNode* newNode = new ListNode(value);
    ListNode* pre = dummyNode;
    ListNode* cur = head;
    while(cur != nullptr && cur->data <= value) {
        pre = cur;
        cur = cur->next;
    }
    newNode->next = cur;
    pre->next = newNode;

    ListNode* resultNode = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return resultNode;
}

ListNode* mergeList(ListNode* head1, ListNode* head2) {
    ListNode* dummyNode = new ListNode(0);
    ListNode* cur = dummyNode;
    while(head1 != nullptr && head2 != nullptr) {
        if(head1->data <= head2->data) {
            cur->next = head1;
            head1 = head1->next;
        }
        else {
            cur->next = head2;
            head2 = head2->next;
        }
        cur = cur->next;
    }
    if(head1 != nullptr) {
        cur->next = head1;
    }
    else if(head2 != nullptr) {
        cur->next = head2;
    }

    cur = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return cur;
}

void clearAllNodes(vector<ListNode*> buckets, ListNode* head) {
    ListNode* nextNode = nullptr;
    while(head != nullptr) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
    int size = buckets.size();
    for(int i = 0; i < size; i++) {
        buckets[i] = nullptr;
    }
}

void bucketSort(vector<int>& arr) {
    vector<ListNode*> buckets(10, (ListNode*)(0));
    int arrSize = arr.size();
    for(int i = 0; i < arrSize; i++) {
        int index = arr[i] / 10;
        ListNode* head = buckets.at(index);
        buckets.at(index) = insertNode(head, arr[i]);
    }
    ListNode* head = buckets.at(0);
    for(int i = 1; i < 10; i++) {
        head = mergeList(head, buckets.at(i));
    }
    for(int i = 0; i < arrSize; i++) {
        arr[i] = head->data;
        head = head->next;
    }

    head = buckets.at(0);
    clearAllNodes(buckets, head);
}

int main()
{
    vector<int> arr = {
        21, 3, 30, 44, 15, 36, 6, 10, 9, 19, 25, 48, 5, 23, 47
    };
    bucketSort(arr);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}
