/* ************************************************************************
> File Name:     LeetCode122.cpp
> Author:        niu0217
> Created Time:  三  2/28 14:27:41 2024
 ************************************************************************/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 1) {
            return 0;
        }
        int result = 0;
        for(int i = 1; i < prices.size(); i++) {
            result += max(0, prices[i] - prices[i - 1]);
        }
        return result;
    }
};
