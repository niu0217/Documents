/* ************************************************************************
> File Name:     LeetCode232.cpp
> Author:        niu0217
> Created Time:  二  2/20 13:10:37 2024
 ************************************************************************/

class MyQueue {
private:
    stack<int> stIn;
    stack<int> stOut;
public:
    MyQueue() {

    }

    void push(int x) {
        stIn.push(x);
    }

    int pop() {
        //特殊判断
        if(this->empty()) {
            return -1;
        }
       if(stOut.empty()) {
           while(!stIn.empty()) {
               stOut.push(stIn.top());
               stIn.pop();
           }
       }
       int topElement = stOut.top();
       stOut.pop();
       return topElement;
    }

    int peek() {
        int topElement = this->pop();
        stOut.push(topElement);
        return topElement;
    }

    bool empty() {
        return stIn.empty() && stOut.empty();
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
