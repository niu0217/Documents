# queue

## 1. 问题

## 2. 引入代码

```c++
#include<iostream>
#include<vector>
#include<stdexcept>

class Queue {
public:
    bool empty() const {
        return elements_.empty();
    }
    size_t size() const {
        return elements_.size();
    }
    void push(int value) {
        elements_.push_back(value);
    }
    int pop() {
        if(empty()) {
            throw std::out_of_range("Queue is empty, cannot dequeue!");
        }
        int front = elements_.front();
        elements_.erase(elements_.begin());
        return front;
    }
    int front() const {
        if(empty()) {
            throw std::out_of_range("Queue is empty, cannot dequeue!");
        }
        return elements_.front();
    }

private:
    std::vector<int> elements_;
};

int main()
{
    Queue que_obj;
    que_obj.push(1);
    que_obj.push(2);
    que_obj.push(3);
    que_obj.push(4);
    que_obj.push(5);
    que_obj.push(6);
    printf("%d\n", que_obj.pop());
    printf("%d\n", que_obj.front());
}
```

## 3. 两个栈实现队列

```c++
#include<iostream>
#include<stack>
#include<stdexcept>

class MyQueue {
public:
    MyQueue() { }
    void push(int x);  //入队
    int pop();  //出队
    int peek();  //取得队首元素
    bool empty() const {
        return input_stack_.empty() && output_stack_.empty();
    }
private:
    //将元素从input_stack_移动到output_stack_.
    //方便可以从output_stack_弹出最旧的元素
    void move_elements();

    std::stack<int> input_stack_;
    std::stack<int> output_stack_;
};

void MyQueue::move_elements() {
    while(input_stack_.size() > 0) {
        int top_value = input_stack_.top();
        output_stack_.push(top_value);
        input_stack_.pop();
    }
}

void MyQueue::push(int x) {
    input_stack_.push(x);
}

int MyQueue::pop() {
    //如果output_stack_是空的，那么将input_stack_赋值给它
    if(output_stack_.empty()) {
        move_elements();
    }
    //如果还是空的，那么就说明队列为空
    if(output_stack_.empty()) {
        throw std::runtime_error("Queue is empty, cannot pop!");
    }
    int front_value = output_stack_.top();
    output_stack_.pop();
    return front_value;
}

int MyQueue::peek() {
    //如果output_stack_是空的，那么将input_stack_赋值给它
    if(output_stack_.empty()) {
        move_elements();
    }
    //如果还是空的，那么就说明队列为空
    if(output_stack_.empty()) {
        throw std::runtime_error("Queue is empty, cannot pop!");
    }
    return output_stack_.top();
}

int main()
{
    MyQueue q;
    q.push(1); // 队列现在是: [1]
    q.push(2); // 队列现在是: [1, 2] (第一个元素是队列的前面)
    std::cout << q.peek() << std::endl; // 返回 1，队列仍然是 [1, 2]
    std::cout << q.pop() << std::endl;  // 返回 1，队列现在是 [2]
    std::cout << q.empty() << std::endl; // 返回 false，队列现在不是空的
    q.push(3); // 将3推入已经包含2的队列，队列现在是 [2, 3]
    std::cout << q.peek() << std::endl; // 返回 2，队列仍然是 [2, 3]
    std::cout << q.pop() << std::endl;  // 返回 2，队列现在是 [3]
    std::cout << q.pop() << std::endl;  // 返回 3，队列现在是空的
    std::cout << q.empty() << std::endl; // 返回 true，因为队列是空的
    return 0;
}
```

