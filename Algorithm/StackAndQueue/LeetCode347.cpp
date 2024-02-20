/* ************************************************************************
> File Name:     LeetCode347.cpp
> Author:        niu0217
> Created Time:  二  2/20 20:14:07 2024
 ************************************************************************/

//小顶堆 + 优先级队列 + 哈希
class Solution {
public:
    struct Compare {
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second; //小顶堆
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //key:   元素
        //value: 该元素出现的次数
        unordered_map<int, int> umap;
        for(int num : nums) {
            umap[num]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> windows;
        for(auto iter = umap.begin(); iter != umap.end(); iter++) {
            windows.push(*iter);
            if(windows.size() > k) {
                windows.pop();
            }
        }
        vector<int> result(k, 0);
        for(int i = k - 1; i >= 0; i--) {
            result[i] = windows.top().first;
            windows.pop();
        }
        return result;
    }
};
