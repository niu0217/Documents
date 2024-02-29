/* ************************************************************************
> File Name:     LeetCode56.cpp
> Author:        niu0217
> Created Time:  四  2/29 15:22:08 2024
 ************************************************************************/

class Solution {
public:
    static bool compare(vector<int>& lhs, vector<int>& rhs) {
        return lhs[0] < rhs[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 1) {
            return intervals;
        }
        sort(intervals.begin(), intervals.end(), compare);
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        for(int i = 1; i < intervals.size(); i++) {
            //有重叠 合并
            if(result.back()[1] >= intervals[i][0]) {
                result.back()[1] = max(intervals[i][1], result.back()[1]);
            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};
