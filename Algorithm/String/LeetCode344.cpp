/* ************************************************************************
> File Name:     LeetCode344.cpp
> Author:        niu0217
> Created Time:  六  2/17 10:28:01 2024
 ************************************************************************/

//使用标准库算法
class Solution {
public:
    void reverseString(vector<char>& s) {
        reverse(s.begin(), s.end());
    }
};

//双指针
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        while(left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
