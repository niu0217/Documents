/* ************************************************************************
> File Name:     LeetCode53.cpp
> Author:        niu0217
> Created Time:  四  2/29 15:42:48 2024
 ************************************************************************/

//暴力  超时
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        for(int i = 0; i < nums.size(); i++) {
            int curSum = 0;
            for(int j = i; j < nums.size(); j++) {
                curSum += nums[j];
                result = curSum > result ? curSum : result;
            }
        }
        return result;
    }
};

//贪心
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN;
        int sum = 0;
        for(int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if(sum > result) {
                result = sum;
            }
            if(sum <= 0) {
                sum = 0;
            }
        }
        return result;
    }
};
