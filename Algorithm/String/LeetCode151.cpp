/* ************************************************************************
> File Name:     LeetCode151.cpp
> Author:        niu0217
> Created Time:  六  2/17 11:11:22 2024
 ************************************************************************/

class Solution {
public:
    void removeExtraSpaces(string& s) {
        int slow = 0;
        for(int fast = 0; fast < s.size(); fast++) {
            if(s[fast] != ' ') {
                //如果不是第一个单词，手动加上空格
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
        s += ' ';
        for(int fast = 0 ; fast < s.size(); fast++) {
            if(s[fast] == ' ') {
                reverse(s.begin() + slow, s.begin() + fast);
                slow = fast + 1;
            }
        }
        s = s.substr(0, s.size() - 1);
        return s;
    }
};

class Solution {
public:
    void removeExtraSpaces(string& s) {
        int slow = 0;
        for(int fast = 0; fast < s.size(); fast++) {
            if(s[fast] != ' ') {
                //如果不是第一个单词，手动加上空格
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
        for(int fast = 0 ; fast <= s.size(); fast++) {
            if(s[fast] == ' ' || fast == s.size()) {
                reverse(s.begin() + slow, s.begin() + fast);
                slow = fast + 1;
            }
        }
        return s;
    }
};
