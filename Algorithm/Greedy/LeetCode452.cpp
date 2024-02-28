/* ************************************************************************
> File Name:     LeetCode452.cpp
> Author:        niu0217
> Created Time:  三  2/28 16:56:15 2024
 ************************************************************************/

class Solution {
public:
    static bool compare(vector<int>& lhs, vector<int>& rhs) {
        return lhs[0] < rhs[0];
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size() == 1) {
            return 1;
        }
        sort(points.begin(), points.end(), compare);
        int result = 1;
        for(int i = 1; i < points.size(); i++) {
            //没有挨着，需要一箭
            if(points[i][0] > points[i - 1][1]) {
                result++;
            }
            else {
                //挨着的时候更新边界
                points[i][1] = min(points[i - 1][1], points[i][1]);
            }
        }
        return result;
    }
};
