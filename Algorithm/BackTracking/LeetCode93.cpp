/* ************************************************************************
> File Name:     LeetCode93.cpp
> Author:        niu0217
> Created Time:  一  2/26 18:28:39 2024
 ************************************************************************/

class Solution {
private:
    vector<string> result;
public:
    bool isValid(const string& s, int idxStart, int idxEnd) {
        if(idxStart > idxEnd) {
            return false;
        }
        //开头不能为0
        if(s[idxStart] == '0' && idxStart != idxEnd) {
            return false;
        }
        int num = 0;
        for(int i = idxStart; i <= idxEnd; i++) {
            if(s[i] > '9' || s[i] < '0') {
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if(num > 255) {
                return false;
            }
        }
        return true;
    }
    void backtracking(string& s, int startIndex, int pointNum) {
       if(pointNum == 3) {
           if(isValid(s, startIndex, s.size() - 1)) {
               result.push_back(s);
           }
           return;
       }
       for(int i = startIndex; i < s.size(); i++) {
           if(isValid(s, startIndex, i)) {
               s.insert(s.begin() + i + 1, '.');
               pointNum++;
               backtracking(s, i + 2, pointNum);
               pointNum--;
               s.erase(s.begin() + i + 1);
           }
           else {
               break;
           }
       }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        result.clear();
        if(s.size() < 4 || s.size() > 12) {
            return {};
        }
        backtracking(s, 0, 0);
        return result;
    }
};
