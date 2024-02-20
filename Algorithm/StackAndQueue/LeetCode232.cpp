/* ************************************************************************
> File Name:     LeetCode232.cpp
> Author:        niu0217
> Created Time:  二  2/20 13:10:37 2024
 ************************************************************************/

class MyQueue {
private:
    stack<int> stackIn;
    stack<int> stackOut;
public:
    MyQueue() {

    }

    void push(int x) {
        stackIn.push(x);
    }

    int pop() {
        if(stackOut.empty()) {
            if(stackIn.empty()) {
                return 0;
            }
            while(!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        int topElement = stackOut.top();
        stackOut.pop();
        return topElement;
    }

    int peek() {
        if(!stackOut.empty()) {
            return stackOut.top();
        }
        if(!stackIn.empty()) {
            stack<int> stackTemp = stackIn;
            while(stackTemp.size() != 1) {
                stackTemp.pop();
            }
            return stackTemp.top();
        }
        return -1;
    }

    bool empty() {
        return stackIn.empty() && stackOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

class MyQueue {
private:
    stack<int> stackIn;
    stack<int> stackOut;
public:
    MyQueue() {

    }

    void push(int x) {
        stackIn.push(x);
    }

    int pop() {
        if(stackOut.empty()) {
            if(stackIn.empty()) {
                return 0;
            }
            while(!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        int topElement = stackOut.top();
        stackOut.pop();
        return topElement;
    }

    int peek() {
        int topElement = this->pop();
        stackOut.push(topElement);
        return topElement;
    }

    bool empty() {
        return stackIn.empty() && stackOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
