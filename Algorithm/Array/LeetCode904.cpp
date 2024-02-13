/* ************************************************************************
> File Name:     LeetCode904.cpp
> Author:        niu0217
> Created Time:  二  2/13 12:35:28 2024
 ************************************************************************/

//滑动窗口
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        //key: 水果种类
        //value： 该种类的水果个数
        unordered_map<int, int> baskets;
        int fruitsSize = fruits.size();
        int maxCanPickedTreeNumbers = 0;
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < fruitsSize; fastIndex++) {
            baskets[fruits[fastIndex]]++;
            while(baskets.size() > 2) {
                baskets[fruits[slowIndex]]--;
                if(baskets[fruits[slowIndex]] == 0) {
                    baskets.erase(fruits[slowIndex]);
                }
                slowIndex++;
            }
            int canPickedTreeNumbers = fastIndex - slowIndex + 1;
            maxCanPickedTreeNumbers = maxCanPickedTreeNumbers > canPickedTreeNumbers 
                                      ? maxCanPickedTreeNumbers : canPickedTreeNumbers;
        }
        return maxCanPickedTreeNumbers;
    }
};
