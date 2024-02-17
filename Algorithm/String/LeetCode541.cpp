/* ************************************************************************
> File Name:     LeetCode541.cpp
> Author:        niu0217
> Created Time:  六  2/17 10:48:49 2024
 ************************************************************************/

class Solution {
public:
    string reverseStr(string s, int k) {
        for(int i = 0; i < s.size(); i += (2 * k)) {
            if(i + k <= s.size()) {
                reverse(s.begin() + i, s.begin() + i + k);
            }
            else {
                reverse(s.begin() + i, s.end());
            }
        }
        return s;
    }
};
