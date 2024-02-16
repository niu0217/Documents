/* ************************************************************************
> File Name:     LeetCode349.cpp
> Author:        niu0217
> Created Time:  五  2/16 14:13:14 2024
 ************************************************************************/

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> resultSet;
        unordered_set<int> nums1Set(begin(nums1), end(nums1));
        for(auto num : nums2) {
            if(nums1Set.find(num) != nums1Set.end()) {
                resultSet.insert(num);
            }
        }
        return vector<int>(begin(resultSet), end(resultSet));
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
