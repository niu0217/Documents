/* ************************************************************************
> File Name:     LeetCode350.cpp
> Author:        niu0217
> Created Time:  五  2/16 14:30:58 2024
 ************************************************************************/

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //保持nums1是较短的那个数组
        if(nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        //key:   元素
        //value: 该元素出现的次数
        unordered_map<int, int> umapNum;
        vector<int> result;
        for(auto num : nums1) {
            umapNum[num]++;
        }
        for(auto num : nums2) {
            if(umapNum[num] != 0) {
                umapNum[num]--;
                result.push_back(num);
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //保持nums1是较短的那个数组
        if(nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }
        //key:   元素
        //value: 该元素出现的次数
        unordered_map<int, int> umapNum;
        vector<int> result;
        for(auto num : nums1) {
            umapNum[num]++;
        }
        for(auto num : nums2) {
            if(umapNum[num] != 0) {
                umapNum[num]--;
                result.push_back(num);
            }
        }
        return result;
    }
};
