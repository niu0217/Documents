/* ************************************************************************
> File Name:     LeetCode438.cpp
> Author:        niu0217
> Created Time:  五  2/16 13:05:21 2024
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
    vector<int> findAnagrams(string s, string p) {
        if(p.size() > s.size()) {
            return {};
        }
        vector<int> result;
        int pSize = p.size();
        int sSize = s.size();
        for(int i = 0; i <= sSize - pSize; i++) {
            string t = s.substr(i, pSize);
            if(isAnagram(t, p)) {
                result.push_back(i);
            }
        }
        return result;
    }
};

//滑动窗口+哈希表
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sSize = s.size();
        int pSize = p.size();
        if(pSize > sSize) {
            return {};
        }
        vector<int> result;
        vector<int> recordsS(26, 0);
        vector<int> recordsP(26, 0);
        for(int i = 0; i < pSize; i++) {
            recordsS[s[i] - 'a']++;
            recordsP[p[i] - 'a']++;
        }
        if(recordsS == recordsP) {
            result.push_back(0);
        }
        for(int slow = 0; slow < sSize - pSize; slow++) {
            recordsS[s[slow] - 'a']--;
            int fast = slow + pSize;
            recordsS[s[fast] - 'a']++;
            if(recordsS == recordsP) {
                result.push_back(slow + 1);
            }
        }
        return result;
    }
};
