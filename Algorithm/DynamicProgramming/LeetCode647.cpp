/* ************************************************************************
> File Name:     LeetCode647.cpp
> Author:        niu0217
> Created Time:  六  3/16 11:01:50 2024
 ************************************************************************/

class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        for(int i = s.size() - 1; i >= 0; i--) {
            for(int j = i; j < s.size(); j++) {
                if(s[i] == s[j]) {
                    if(j - i <= 1) {
                        result++;
                        dp[i][j] = true;
                    }
                    else if(dp[i + 1][j - 1] == true) {
                        result++;
                        dp[i][j] = true;
                    }
                }
            }
        }
        return result;
    }
};
