/* ************************************************************************
> File Name:     LeetCode406.cpp
> Author:        niu0217
> Created Time:  三  2/28 15:38:14 2024
 ************************************************************************/

class Solution {
public:
    static bool compare(vector<int>& lhs, vector<int>& rhs) {
        //身高相同的时候，以下标为维度从小到大排序
        if(lhs[0] == rhs[0]) {
            return lhs[1] < rhs[1];
        }
        //身高不同的时候，以身高为维度从大到小排序
        return lhs[0] >rhs[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), compare);
        vector<vector<int>> result;
        for(int i = 0; i < people.size(); i++) {
            int position = people[i][1];
            result.insert(result.begin() + position, people[i]);
        }
        return result;
    }
};

class Solution {
public:
    static bool compare(vector<int>& lhs, vector<int>& rhs) {
        //身高相同的时候，以下标为维度从小到大排序
        if(lhs[0] == rhs[0]) {
            return lhs[1] < rhs[1];
        }
        //身高不同的时候，以身高为维度从大到小排序
        return lhs[0] >rhs[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), compare);
        list<vector<int>> resultList;
        for(int i = 0; i < people.size(); i++) {
            int position = people[i][1];
            auto iter = resultList.begin();
            while(position--) {
                iter++;
            }
            resultList.insert(iter, people[i]);
        }
        return vector<vector<int>>(resultList.begin(), resultList.end());
    }
};
