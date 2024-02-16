/* ************************************************************************
> File Name:     LeetCode242.cpp
> Author:        niu0217
> Created Time:  五  2/16 11:30:01 2024
 ************************************************************************/

class Solution {
public:
    bool isAnagram(string s, string t) {
        int records[26] = {0};
        for(int i = 0; i < s.size(); i++) {
            records[s[i] - 'a']++;
        }
        for(int i = 0; i < t.size(); i++) {
            records[t[i] - 'a']--;
        }
        for(int i = 0; i < 26; i++) {
            if(records[i] != 0) {
                return false;
            }
        }
        return true;
    }
};
