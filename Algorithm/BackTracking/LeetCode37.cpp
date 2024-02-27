/* ************************************************************************
> File Name:     LeetCode37.cpp
> Author:        niu0217
> Created Time:  二  2/27 15:48:41 2024
 ************************************************************************/

class Solution {
public:
    bool isValid(int row, int col, char val, vector<vector<char>>& board) {
        //行
        for(int i = 0; i < 9; i++) {
            if(board[i][col] == val) {
                return false;
            }
        }
        //列
        for(int j = 0; j < 9; j++) {
            if(board[row][j] == val) {
                return false;
            }
        }
        //3*3
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for(int i = startRow; i < startRow + 3; i++) {
            for(int j = startCol; j < startCol + 3; j++) {
                if(board[i][j] == val) {
                    return false;
                }
            }
        }
        return true;
    }
    bool backtracking(vector<vector<char>>& board) {
       for(int i = 0; i < board.size(); i++) {
           for(int j = 0; j < board[0].size(); j++) {
               if(board[i][j] == '.') {
                   for(char k = '1'; k <= '9'; k++) {
                       if(isValid(i, j, k, board)) {
                           board[i][j] = k;
                           if(backtracking(board)) {
                               return true;
                           }
                           board[i][j] = '.';
                       }
                   }
                   return false;
               }
           }
       }
       return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};
