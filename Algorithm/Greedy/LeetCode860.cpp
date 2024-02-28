/* ************************************************************************
> File Name:     LeetCode860.cpp
> Author:        niu0217
> Created Time:  三  2/28 11:43:48 2024
 ************************************************************************/

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        //分情况讨论
        int five = 0;
        int ten = 0;
        int twenty = 0;
        for(int bill : bills) {
            if(bill == 5) {
                five++;
            }
            else if(bill == 10) {
                if(five > 0) {
                    five--;
                    ten++;
                }
                else {
                    return false;
                }
            }
            else if(bill == 20) {
                if(ten > 0 && five > 0) {
                    ten--;
                    five--;
                    twenty++;
                }
                else if(five >= 3) {
                    five -= 3;
                    twenty++;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
};
