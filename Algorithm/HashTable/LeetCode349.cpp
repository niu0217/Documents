/* ************************************************************************
> File Name:     LeetCode349.cpp
> Author:        niu0217
> Created Time:  五  2/16 14:13:14 2024
 ************************************************************************/

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> usetNum(nums1.begin(), nums1.end());
        unordered_set<int> usetResult;
        for(int num : nums2) {
            if(usetNum.find(num) != usetNum.end()) {
                usetResult.insert(num);
            }
        }
        return vector<int>{usetResult.begin(), usetResult.end()};
    }
};

//使用数组模拟哈希表
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> resultSet;
        int hash[1001] = {0};
        for(auto num : nums1) {
            hash[num] = 1;
        }
        for(auto num : nums2) {
            if(hash[num] == 1) {
                resultSet.insert(num);
            }
        }
        return vector<int>(begin(resultSet), end(resultSet));
    }
};
