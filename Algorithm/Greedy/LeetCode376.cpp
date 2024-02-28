/* ************************************************************************
> File Name:     LeetCode376.cpp
> Author:        niu0217
> Created Time:  三  2/28 12:09:00 2024
 ************************************************************************/

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        //情况一：上下坡中有平坡
        //情况二：数组首尾两端
        //情况三：单调坡度有平坡
        if(nums.size() == 1) {
            return 1;
        }
        int preDiff = 0;
        int curDiff = 0;
        int result = 1;
        for(int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            if((preDiff >= 0 && curDiff < 0) || (preDiff <= 0 && curDiff > 0)) {
                result++;
                preDiff = curDiff;
            }
        }
        return result;
    }
};
