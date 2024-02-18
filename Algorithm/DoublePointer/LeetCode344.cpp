/* ************************************************************************
> File Name:     LeetCode344.cpp
> Author:        niu0217
> Created Time:  日  2/18 13:22:13 2024
 ************************************************************************/

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        while(left < right) {
            swap(s[left++], s[right--]);
        }
    }
};
