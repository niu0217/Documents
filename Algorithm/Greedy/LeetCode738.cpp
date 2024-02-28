/* ************************************************************************
> File Name:     LeetCode738.cpp
> Author:        niu0217
> Created Time:  三  2/28 13:58:16 2024
 ************************************************************************/

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string strNum = to_string(n);
        int flag = strNum.size();
        for(int i = strNum.size() - 1; i > 0; i--) {
            if(strNum[i - 1] > strNum[i]) {
                flag = i;
                strNum[i - 1]--;
            }
        }
        for(int i = flag; i < strNum.size(); i++) {
            strNum[i] = '9';
        }
        return stoi(strNum);
    }
};
