/* ************************************************************************
> File Name:     LeetCode202.cpp
> Author:        niu0217
> Created Time:  五  2/16 15:15:25 2024
 ************************************************************************/

class Solution {
public:
    int getSum(int n) {
        int sum = 0;
        while(n > 0) {
            sum += (n % 10) * (n % 10);
            n = n / 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> uset;
        while(true) {
            n = getSum(n);
            if(n == 1) {
                return true;
            }
            if(uset.find(n) != uset.end()) {
                break;
            }
            uset.insert(n);
        }
        return false;
    }
};
