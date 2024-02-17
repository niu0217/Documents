/* ************************************************************************
> File Name:     LeetCode28.cpp
> Author:        niu0217
> Created Time:  六  2/17 14:38:06 2024
 ************************************************************************/

//暴力
class Solution {
public:
    int strStr(string haystack, string needle) {
        for(int i = 0; i < haystack.size(); i++) {
            int count = 0;
            int curIndex = i;
            for(int j = 0; j < needle.size(); j++) {
                if(haystack[curIndex] == needle[j]) {
                    curIndex++;
                    count++;
                    if(count == needle.size()) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }
};

//KMP
class Solution {
public:
    void getPrefix(string s, vector<int>& prefix) {
        //i的含义：后缀末尾
        //j的含义：前缀末尾
        int j = 0;
        prefix[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while(j > 0 && s[i] != s[j]) {
                j = prefix[j - 1];
            }
            if(s[i] == s[j]) {
                j++;
            }
            prefix[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int j = 0;
        vector<int> prefix(needle.size(), 0);
        getPrefix(needle, prefix);
        for(int i = 0; i < haystack.size(); i++) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = prefix[j - 1];
            }
            if(haystack[i] == needle[j]) {
                j++;
            }
            if(j == needle.size()) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

//KMP -1
class Solution {
public:
    void getNext(string s, vector<int>& next) {
        //i的含义：后缀末尾
        //j的含义：前缀末尾
        int j = -1;
        next[0] = -1;
        for(int i = 1; i < s.size(); i++) {
            while(j >= 0 && s[i] != s[j + 1]) {
                j = next[j];
            }
            if(s[i] == s[j + 1]) {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int j = -1;
        vector<int> next(needle.size(), 0);
        getNext(needle, next);
        for(int i = 0; i < haystack.size(); i++) {
            while(j >= 0 && haystack[i] != needle[j + 1]) {
                j = next[j];
            }
            if(haystack[i] == needle[j + 1]) {
                j++;
            }
            if(j == needle.size() - 1) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};
