# stack

## 1. 问题

## 2. 引入代码

```c++
#include<iostream>
#include<vector>
#include<stdexcept>

class Stack {
public:
    void push(int elem);
    void pop();
    int top() const;
    bool is_empty() const {
        return elems_.empty();
    }

private:
    std::vector<int> elems_;  //使用vector作为实现栈的底层容器
};

void Stack::push(int elem) {
    elems_.push_back(elem);
}

void Stack::pop() {
    if(is_empty()) {
        throw std::out_of_range("Stack<>::pop():empty Stack");
    }
    elems_.pop_back();
}

int Stack::top() const {
    if(is_empty()) {
        throw std::out_of_range("Stack<>::pop():empty Stack");
    }
    return elems_.back();
}

int main()
{
    try {
        Stack stack;
        stack.push(7);
        std::cout << stack.top() << std::endl; // 输出：7
        stack.pop();
        std::cout << stack.is_empty() << std::endl; // 输出：1（true）
        stack.top(); // 将会抛出std::out_of_range异常，因为栈是空的
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl; // 输出异常信息
        return -1; // 返回非零值表示程序异常终止
    }
    return 0; // 程序正常退出，返回0值
}
```

## 3. 用queue实现栈

```c++
#include<iostream>
#include<queue>
#include<stdexcept>

template<typename T>
class Stack {
public:
    void push(const T& value);
    T pop();
    T top() const;
    bool empty() const {
        return q1_.empty();
    }

private:
    void move_elements();  //将元素从q1_移动到q2_,除了最后一个元素

    std::queue<T> q1_;  //主队列
    std::queue<T> q2_;  //辅助队列，主要用于保存临时数据
};

template<typename T>
void Stack<T>::move_elements() {
    while(q1_.size() > 1) {
        q2_.push(q1_.front());
        q1_.pop();
    }
}

template<typename T>
void Stack<T>::push(const T& value) {
    q1_.push(value);
}

template<typename T>
T Stack<T>::pop() {
    if(q1_.empty()) {
        throw std::out_of_range("Stack is empty!");
    }

    move_elements();

    T top_value = q1_.front();
    q1_.pop();

    std::swap(q1_, q2_);  //将q1_的数据恢复，除了第一个元素

    return top_value;
}

template<typename T>
T Stack<T>::top() const {
    if(q1_.empty()) {
        throw std::out_of_range("Stack is empty!");
    }
    std::queue<T> temp_queue = q1_;  //为了不改变q1_本身
    while(temp_queue.size() > 1) {
        temp_queue.pop();
    }
    return temp_queue.front();  //此时只剩最后一个元素
}

int main()
{
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    printf("%d\n", st.top());
    printf("%d\n", st.pop());
    printf("%d\n", st.top());
}
```

