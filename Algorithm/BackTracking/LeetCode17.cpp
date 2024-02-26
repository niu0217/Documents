/* ************************************************************************
> File Name:     LeetCode17.cpp
> Author:        niu0217
> Created Time:  一  2/26 13:57:42 2024
 ************************************************************************/

class Solution {
private:
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };
public:
    vector<string> result;
    string path = "";
    void backtracking(string& digits, int index) {
        //树的深度: digits.size()
        if(index == digits.size()) {
            result.push_back(path);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap[digit];
        for(int i = 0; i < letters.size(); i++) {
            path.push_back(letters[i]);
            backtracking(digits, index + 1);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        if(digits.size() == 0) {
            return {};
        }
        backtracking(digits, 0);
        return result;
    }
};
