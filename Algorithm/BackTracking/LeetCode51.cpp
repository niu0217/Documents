/* ************************************************************************
> File Name:     LeetCode51.cpp
> Author:        niu0217
> Created Time:  二  2/27 14:53:29 2024
 ************************************************************************/

class Solution {
private:
    vector<vector<string>> result;
public:
    bool isValid(vector<string>& chessboard, int row, int col, int n) {
        //是否同列
        for(int i = 0; i < row; i++) {
            if(chessboard[i][col] == 'Q') {
                return false;
            }
        }
        //是否同45度
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if(chessboard[i][j] == 'Q') {
                return false;
            }
        }
        //是否同135度
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if(chessboard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
    void backtracking(int n, int row, vector<string>& chessboard) {
        if(row == n) {
            result.push_back(chessboard);
            return;
        }
        for(int col = 0; col < n; col++) {
            if(isValid(chessboard, row, col, n)) {
                chessboard[row][col] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
            else {
                continue;
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessboard(n, string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};
