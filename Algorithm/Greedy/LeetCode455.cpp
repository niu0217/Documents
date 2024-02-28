/* ************************************************************************
> File Name:     LeetCode455.cpp
> Author:        niu0217
> Created Time:  三  2/28 10:33:34 2024
 ************************************************************************/

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int count = 0;
        int j = s.size() - 1;
        int i = g.size() - 1;
        while(i >= 0 && j >= 0) {
            if(s[j] >= g[i]) {
                j--;
                i--;
                count++;
            }
            else {
                i--;
            }
        }
        return count;
    }
};
