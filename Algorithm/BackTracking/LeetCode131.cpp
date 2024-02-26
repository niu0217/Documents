/* ************************************************************************
> File Name:     LeetCode131.cpp
> Author:        niu0217
> Created Time:  一  2/26 17:26:08 2024
 ************************************************************************/

class Solution {
private:
    vector<vector<string>> result;
    vector<string> path;
public:
    bool isPalindrome(string& s, int idxLeft, int idxRight) {
        int i = idxLeft;
        int j = idxRight;
        for(; i < j; i++,j--) {
            if(s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
    void backtracking(string& s, int startIndex) {
        if(startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for(int i = startIndex; i < s.size(); i++) {
            //切割
            if(isPalindrome(s, startIndex, i)) {
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            }
            else {
                continue;
            }
            backtracking(s, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        path.clear();
        backtracking(s, 0);
        return result;
    }
};
