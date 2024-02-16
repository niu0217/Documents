/* ************************************************************************
> File Name:     LeetCode383.cpp
> Author:        niu0217
> Created Time:  五  2/16 11:54:05 2024
 ************************************************************************/

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if(ransomNote.size() > magazine.size()) {
            return false;
        }
        int records[26] = {0};
        for(int i = 0; i < magazine.size(); i++) {
            records[magazine[i] - 'a']++;
        }
        for(int i = 0; i < ransomNote.size(); i++) {
            records[ransomNote[i] - 'a']--;
            if(records[ransomNote[i] - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};
