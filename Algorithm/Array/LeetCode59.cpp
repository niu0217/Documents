/* ************************************************************************
> File Name:     LeetCode59.cpp
> Author:        niu0217
> Created Time:  二  2/13 17:53:45 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n, 0));
        int startX = 0;
        int startY = 0;
        int loop = n / 2;
        int mid = n / 2;
        int count = 1;
        int offset = 1;
        int i;
        int j;
        while(loop--) {
            i = startX;
            j = startY;

            //从左到右
            for(j = startY; j < n - offset; j++) {
                result[startX][j] = count++;
            }
            //从上到下
            for(i = startX; i < n - offset; i++) {
                result[i][j] = count++;
            }
            //从右到左
            for(; j > startY; j--) {
                result[i][j] = count++;
            }
            //从下到上
            for(; i > startX; i--) {
                result[i][j] = count++;
            }

            startX++;
            startY++;
            offset += 1;
        }
        if(n % 2) {
            result[mid][mid] = count;
        }
        return result;
    }
};
