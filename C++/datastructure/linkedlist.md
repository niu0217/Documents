# linkedlist

## 1. 问题

## 2. 引入代码

```c++
#include<iostream>

//链表节点
class Node {
public:
    int data_;
    Node *next_;
    Node(int d): data_(d), next_(nullptr) { }
};

//链表类
class LinkedList {
public:
    LinkedList(): head_(nullptr), tail_(nullptr), size_(0) { }
    ~LinkedList() {
        clear();
    }

    //链表操作
    void clear();  //清空链表
    void append(int data);  //插入到链表尾部
    void insert_at(int index, int data);  //在指定位置插入数据
    void remove_at(int index);  //删除指定位置的数据
    int find(int data);  //查找数据所在位置，不存在返回-1

    //辅助函数
    void print_linked_list();  //打印链表

private:
    Node *head_;
    Node *tail_;
    int size_;
};

void LinkedList::clear() {
    Node *current_node = head_;
    Node *next_node = nullptr;
    while(current_node != nullptr) {
        next_node = current_node->next_;
        delete current_node;
        current_node = next_node;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
}

void LinkedList::append(int data) {
    Node *new_node = new Node(data);
    if(head_ == nullptr) {
        head_ = tail_ = new_node;
    }
    else {
        tail_->next_ = new_node;
        tail_ = new_node;
    }
    size_++;
}

void LinkedList::insert_at(int index, int data) {
    if(index < 0 || index > size_) {  //index不合法
        std::cout<<"Index out of range."<<std::endl;
        return;
    }
    if(index == 0) {  //index在头部
        Node *new_node = new Node(data);
        new_node->next_ = head_;
        head_ = new_node;
    }
    else { //index在中间位置或者尾部
        Node *prev_node = head_;
        //找到要插入位置的前一个节点
        for(int i = 0; i < index - 1; i++) {
            prev_node = prev_node->next_;
        }
        Node *new_node = new Node(data);
        new_node->next_ = prev_node->next_;
        prev_node->next_ = new_node;
        if(prev_node == tail_) {  //刚好要在尾部插入元素
            tail_ = new_node;
        }
    }
    size_++;
}

void LinkedList::remove_at(int index) {
    if(index < 0 || index > size_) { //index不合法
        std::cout<<"Index out of range."<<std::endl;
        return;
    }
    if(index == 0) {  //index在头部
        Node *next_node = head_->next_;
        delete head_;
        head_ = next_node;
        if(head_ == nullptr) {  //链表为空,则更新尾节点
            tail_ = nullptr;
        }
    }
    else {  //index在中间位置或者尾部
        Node *prev_node = head_;
        //找到要删除位置的前一个节点
        for(int i = 0; i < index - 1; i++) {
            prev_node = prev_node->next_;
        }
        Node *to_del_node = prev_node->next_;
        prev_node->next_ = to_del_node->next_;
        if(to_del_node == tail_) {  //要删除的节点刚好是尾节点需要更新尾节点
            tail_ = prev_node;
        }
        delete to_del_node;
    }
    size_--;
}

int LinkedList::find(int data) {
    Node *current_node = head_;
    for(int i = 0; i < size_; i++) {
        if(current_node->data_ == data) {
            return i;
        }
        current_node = current_node->next_;
    }
    return -1;  //不在链表中
}

void LinkedList::print_linked_list() {
    Node *current_node = head_;
    while(current_node != nullptr) {
        std::cout<<current_node->data_<<"  ";
        current_node = current_node->next_;
    }
    printf("\n");
}

int main()
{
    LinkedList *linked_list = new LinkedList;
    linked_list->append(10);
    linked_list->append(20);
    linked_list->append(30);
    linked_list->append(40);
    linked_list->append(50);
    linked_list->append(60);
    linked_list->append(70);
    linked_list->append(80);
    linked_list->append(90);
    linked_list->append(100);
    linked_list->print_linked_list();

    linked_list->insert_at(5, 999);
    linked_list->print_linked_list();

    linked_list->remove_at(7);
    linked_list->print_linked_list();

    if(linked_list->find(40)) {
        std::cout<<"Find ...."<<std::endl;
    }
    else {
        std::cout<<"Not find..."<<std::endl;
    }

    return 0;
}
```

## 3. 扩展

### 3.1 反转链表

```c++
void LinkedList::reverse() {
    if(size_ == 1) {  //只有一个节点不需要反转
        return;
    }
    Node *prev_node = head_;
    Node *current_node = head_->next_;
    Node *next_node = current_node->next_;
    while(current_node && current_node->next_) {
        current_node->next_ = prev_node;
        prev_node = current_node;
        current_node = next_node;
        next_node = current_node->next_;
    }
    current_node->next_ = prev_node;
    tail_ = head_;
    tail_->next_ = nullptr;
    head_ = current_node;
}
```

