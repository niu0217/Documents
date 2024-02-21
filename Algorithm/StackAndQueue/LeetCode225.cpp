/* ************************************************************************
> File Name:     LeetCode225.cpp
> Author:        niu0217
> Created Time:  二  2/20 13:23:31 2024
 ************************************************************************/

class MyStack {
private:
    queue<int> que;
public:
    MyStack() {

    }

    void push(int x) {
        que.push(x);
    }

    int pop() {
        //特殊判断
        if(que.empty()) {
            return -1;
        }
        int size = que.size();
        size--;
        while(size) {
            que.push(que.front());
            que.pop();
            size--;
        }
        int topElement = que.front();
        que.pop();
        return topElement;
    }

    int top() {
        return que.back();
    }

    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
