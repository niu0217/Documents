/* ************************************************************************
> File Name:     LeetCode134.cpp
> Author:        niu0217
> Created Time:  四  2/29 16:08:04 2024
 ************************************************************************/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalSum = 0;
        int count = 0;
        int start = 0;
        for(int i = 0; i < gas.size(); i++) {
            count += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if(count < 0) {
                start = i + 1;
                count = 0;
            }
        }
        if(totalSum < 0) {
            return -1;
        }
        return start;
    }
};
