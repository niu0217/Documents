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
        Myqueue windows;
        vector<int> result;
        for(int i = 0; i < k; i++) {
            windows.push(nums[i]);
        }
        result.push_back(windows.front());
        for(int i = k; i < nums.size(); i++) {
            windows.pop(nums[i - k]);
            windows.push(nums[i]);
            result.push_back(windows.front());
        }
        return result;
    }
};

//使用multiset
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> windows;
        vector<int> result;
        for(int i = 0; i < k; i++) {
            windows.insert(nums[i]);
        }
        result.push_back(*windows.rbegin());
        for(int i = k; i < nums.size(); i++) {
            auto iter = windows.find(nums[i - k]);
            if(iter != windows.end()) {
                windows.erase(iter);
            }
            windows.insert(nums[i]);
            result.push_back(*windows.rbegin());
        }
        return result;
    }
};
