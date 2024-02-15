/* ************************************************************************
> File Name:     LeetCode904.cpp
> Author:        niu0217
> Created Time:  二  2/13 12:35:28 2024
 ************************************************************************/

//滑动窗口
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        //key:   水果种类
        //value: 该种类数量
        unordered_map<int, int> baskets;
        const int MAX_FRUITS_TYPES = 2;
        int maxCanPickedTrees = INT_MIN;
        int curCanPickedTrees = 0;
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < fruits.size(); fastIndex++) {
            baskets[fruits[fastIndex]]++;
            while(baskets.size() > MAX_FRUITS_TYPES) {
                baskets[fruits[slowIndex]]--;
                if(baskets[fruits[slowIndex]] == 0) {
                    baskets.erase(fruits[slowIndex]);
                }
                slowIndex++;
            }
            curCanPickedTrees = fastIndex - slowIndex + 1;
            maxCanPickedTrees = max(curCanPickedTrees, maxCanPickedTrees);
        }
        return maxCanPickedTrees;
    }
};
