/* ************************************************************************
> File Name:     LeetCode435.cpp
> Author:        niu0217
> Created Time:  四  2/29 14:30:02 2024
 ************************************************************************/

class Solution {
public:
    static bool compare(vector<int>& lhs, vector<int>& rhs) {
        return lhs[1] < rhs[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), compare);
        int count = 1; //记录非交叉区间
        int endBorder = intervals[0][1];
        for(int i = 1; i < intervals.size(); i++) {
            if(endBorder <= intervals[i][0]) {
                count++;
                endBorder = intervals[i][1];
            }
        }
        return intervals.size() - count;
    }
};
