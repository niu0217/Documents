/* ************************************************************************
> File Name:     LeetCode225.cpp
> Author:        niu0217
> Created Time:  二  2/20 13:23:31 2024
 ************************************************************************/

class MyStack {
private:
    queue<int> queIn;
    queue<int> queOut;
public:
    MyStack() {

    }

    void push(int x) {
        queIn.push(x);
    }

    int pop() {
        if(queIn.empty()) {
            return -1;
        }
        while(queIn.size() != 1) {
            queOut.push(queIn.front());
            queIn.pop();
        }
        int topElement = queIn.front();
        queIn.pop();
        queIn.swap(queOut);
        return topElement;
    }

    int top() {
        return queIn.back();
    }

    bool empty() {
        return queIn.empty();
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
