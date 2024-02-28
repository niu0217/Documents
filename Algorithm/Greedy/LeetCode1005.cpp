/* ************************************************************************
> File Name:     LeetCode1005.cpp
> Author:        niu0217
> Created Time:  三  2/28 10:48:28 2024
 ************************************************************************/

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        //每次取最小的
        for(;k > 0; k--) {
            int minVaule = INT_MAX;
            int minIndex = 0;
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i] < minVaule) {
                    minVaule = nums[i];
                    minIndex = i;
                }
            }
            nums[minIndex] = -nums[minIndex];
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum;
    }
};

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        //每次取最小的
        for(;k > 0; k--) {
            auto minIter = min_element(nums.begin(), nums.end());
            int minIndex = distance(nums.begin(), minIter);
            nums[minIndex] = -nums[minIndex];
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum;
    }
};

class Solution {
public:
    static bool compare(int a, int b) {
        return abs(a) > abs(b);
    }
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        //按照绝对值大小从大到小排序
        sort(nums.begin(), nums.end(), compare);
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] < 0 && k > 0) {
                nums[i] *= -1;
                k--;
            }
        }
        //反复转变数值最小的元素
        if(k % 2 == 1) {
            nums[nums.size() - 1] *= -1;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum;
    }
};
