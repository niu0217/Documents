/* ************************************************************************
> File Name:     LeetCode135.cpp
> Author:        niu0217
> Created Time:  三  2/28 14:58:02 2024
 ************************************************************************/

class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> candyVec(ratings.size(), 1);
        //从左向右，比较当前孩子和左孩子的评分
        for(int i = 1; i < ratings.size(); i++) {
            if(ratings[i] > ratings[i - 1]) {
                candyVec[i] = candyVec[i - 1] + 1;
            }
        }
        //从右向左，比较当前孩子和右孩子的评分
        for(int i = ratings.size() - 2; i >= 0; i--) {
            if(ratings[i] > ratings[i + 1]) {
                candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
            }
        }
        //统计
        int sum = accumulate(candyVec.begin(), candyVec.end(), 0);
        return sum;
    }
};
