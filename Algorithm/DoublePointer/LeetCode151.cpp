/* ************************************************************************
> File Name:     LeetCode151.cpp
> Author:        niu0217
> Created Time:  日  2/18 13:25:11 2024
 ************************************************************************/

class Solution {
public:
    void removeExtraSpaces(string& s) {
        int slow = 0;
        for(int fast = 0; fast < s.size(); fast++) {
            if(s[fast] != ' ') {
                if(slow != 0) {
                    s[slow++] = ' ';
                }
                while(fast < s.size() && s[fast] != ' ') {
                    s[slow++] = s[fast++];
                }
            }
        }
        s.resize(slow);
    }
    string reverseWords(string s) {
        removeExtraSpaces(s);
        reverse(s.begin(), s.end());
        int slow = 0;
        for(int fast = 0; fast <= s.size(); fast++) {
            if(s[fast] == ' ' || fast == s.size()) {
                reverse(s.begin() + slow, s.begin() + fast);
                slow = fast + 1;
            }
        }
        return s;
    }
};
