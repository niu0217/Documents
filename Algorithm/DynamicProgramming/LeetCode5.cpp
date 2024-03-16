/* ************************************************************************
> File Name:     LeetCode5.cpp
> Author:        niu0217
> Created Time:  六  3/16 12:04:48 2024
 ************************************************************************/

class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        string maxStr = "";
        for(int i = s.size() - 1; i >= 0; i--) {
            for(int j = i; j < s.size(); j++) {
                if(s[i] == s[j]) {
                    if(j - i <= 1) {
                        dp[i][j] = true;
                        if(j - i + 1 > maxStr.size()) {
                            maxStr = s.substr(i, j - i + 1);
                        }
                    }
                    else {
                        if(dp[i + 1][j - 1]) {
                            dp[i][j] = true;
                            if(j - i + 1 > maxStr.size()) {
                                maxStr = s.substr(i, j - i + 1);
                            }
                        }
                    }
                }
            }
        }
        return maxStr;
    }
};
