/* ************************************************************************
> File Name:     LeetCode45.cpp
> Author:        niu0217
> Created Time:  三  2/28 16:17:11 2024
 ************************************************************************/

class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size() == 1) {
            return 0;
        }
        int curDistance = 0; //当前覆盖的最大距离
        int nextDistance = 0; //下一步覆盖的最大距离
        int minStep = 0;
        for(int i = 0; i < nums.size(); i++) {
            nextDistance = max(nextDistance, i + nums[i]);
            if(curDistance == i) {
                minStep++;
                curDistance = nextDistance;
                if(nextDistance >= nums.size() - 1) {
                    break;
                }
            }
        }
        return minStep;
    }
};
