/* ************************************************************************
> File Name:     LeetCode54.cpp
> Author:        niu0217
> Created Time:  二  2/13 17:58:38 2024
 ************************************************************************/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int rowBegin = 0;
        int rowEnd = matrix.size() - 1;
        int columnBegin = 0;
        int columnEnd = matrix[0].size() - 1;
        vector<int> result;
        while(true) {
            //从左到右
            for(int j = columnBegin; j <= columnEnd; j++) {
                result.push_back(matrix[rowBegin][j]);
            }
            //从上到下
            if(++rowBegin > rowEnd) {
                break;
            }
            for(int i = rowBegin; i <= rowEnd; i++) {
                result.push_back(matrix[i][columnEnd]);
            }
            //从右到左
            if(columnBegin > --columnEnd) {
                break;
            }
            for(int j = columnEnd; j >= columnBegin; j--) {
                result.push_back(matrix[rowEnd][j]);
            }
            //从下到上
            if(rowBegin > --rowEnd) {
                break;
            }
            for(int i = rowEnd; i >= rowBegin; i--) {
                result.push_back(matrix[i][columnBegin]);
            }
            if(++columnBegin > columnEnd) {
                break;
            }
        }
        return result;
    }
};
