/* ************************************************************************
> File Name:     LeetCode239.cpp
> Author:        niu0217
> Created Time:  二  2/20 17:17:16 2024
 ************************************************************************/

//超出时间限制
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<int, vector<int>> windows;
        vector<int> result;
        for(int i = 0; i < k; i++) {
            windows.push(nums[i]);
        }
        result.push_back(windows.top());
        if(nums.size() <= k) {
            return result;
        }
        int count;
        for(int i = 1; i <= (nums.size() - k); i++) {
            windows = priority_queue<int, vector<int>>();
            count = 0;
            int j = i;
            while(j < nums.size() && count < k) {
                windows.push(nums[j]);
                j++;
                count++;
            }
            result.push_back(windows.top());
        }
        return result;
    }
};

//自己实现一个单调队列
class Solution {
public:
    class Myqueue {
    private:
        deque<int> deq;
    public:
        void push(int value) {
            while(!deq.empty() && value > deq.back()) {
                deq.pop_back();
            }
            deq.push_back(value);
        }
        void pop(int value) {
            if(!deq.empty() && value == deq.front()) {
                deq.pop_front();
            }
        }
        int front() {
            return deq.front();
        }
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Myqueue myqueue;
        vector<int> result;
        for(int i = 0; i < k; i++) {
            myqueue.push(nums[i]);
        }
        result.push_back(myqueue.front());
        for(int i = k; i < nums.size(); i++) {
            myqueue.pop(nums[i - k]);
            myqueue.push(nums[i]);
            result.push_back(myqueue.front());
        }
        return result;
    }
};

//使用multiset
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> maxValuesSet;
        vector<int> result;
        for(int i = 0; i < nums.size(); i++) {
            if(i >= k) {
                maxValuesSet.erase(maxValuesSet.find(nums[i - k]));
            }
            maxValuesSet.insert(nums[i]);
            if(i >= k - 1) {
                result.push_back(*(maxValuesSet.rbegin()));
            }
        }
        return result;
    }
};
