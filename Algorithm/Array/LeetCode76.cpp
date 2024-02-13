/* ************************************************************************
> File Name:     LeetCode76.cpp
> Author:        niu0217
> Created Time:  二  2/13 13:45:35 2024
 ************************************************************************/

class Solution {
public:
    string minWindow(string s, string t) {
        //key: 字符
        //value：该字符出现的次数
        unordered_map<char, int> umapT;
        unordered_map<char, int> umapS;
        string minMatchStr = "";
        for(auto ch : t) {
            umapT[ch]++;
        }
        int countTimes = 0;
        int j = 0;
        for(int i = 0; i < s.size(); i++) {
            umapS[s[i]]++;
            if(umapS[s[i]] <= umapT[s[i]]) {
                countTimes++;
            }
            //边界调整
            while(umapS[s[j]] > umapT[s[j]]) {
                umapS[s[j++]]--;
            }
            if(countTimes == t.size()) {
                if(minMatchStr == "" || (i - j + 1) < minMatchStr.size()) {
                    minMatchStr = s.substr(j, i - j + 1);
                }
            }
        }
        return minMatchStr;
    }
};
