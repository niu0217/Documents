/* ************************************************************************
> File Name:     LeetCode474.cpp
> Author:        niu0217
> Created Time:  六  3/16 15:35:30 2024
 ************************************************************************/

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for(string str : strs) {
            int x = 0;
            int y = 0;
            for(char c : str) {
                if(c == '0') {
                    x++;
                }
                else {
                    y++;
                }
            }
            for(int i = m; i >= x; i--) {
                for(int j = n; j >= y; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - x][j - y] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
