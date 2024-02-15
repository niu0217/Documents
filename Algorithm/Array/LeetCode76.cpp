/* ************************************************************************
> File Name:     LeetCode76.cpp
> Author:        niu0217
> Created Time:  二  2/13 13:45:35 2024
 ************************************************************************/

class Solution {
public:
    string minWindow(string s, string t) {
        //key:   字符
        //vaule: 该字符出现的次数
        unordered_map<char, int> umapS;
        unordered_map<char, int> umapT;
        for(auto ch : t) {
            umapT[ch]++;
        }
        string minMatchStr = "";
        int countTimes = 0; //t中字符在s中出现的次数
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < s.size(); fastIndex++) {
            umapS[s[fastIndex]]++;
            if(umapS[s[fastIndex]] <= umapT[s[fastIndex]]) {
                countTimes++;
            }
            //边界调整
            while(umapS[s[slowIndex]] > umapT[s[slowIndex]]) {
                umapS[s[slowIndex]]--;
                slowIndex++;
            }
            if(countTimes == t.size()) {
                int curStrLength = fastIndex - slowIndex + 1;
                if(minMatchStr == "" || curStrLength < minMatchStr.size()) {
                    minMatchStr = s.substr(slowIndex, curStrLength);
                }
            }
        }
        return minMatchStr;
    }
};
