/* ************************************************************************
> File Name:     LeetCode49.cpp
> Author:        niu0217
> Created Time:  五  2/16 12:45:06 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> umapStrs;
        for(const auto& s : strs) {
            string sortS = s;
            sort(begin(sortS), end(sortS));
            umapStrs[sortS].push_back(s);
        }
        for(const auto& element : umapStrs) {
            result.push_back(element.second);
        }
        return result;
    }
};
