/* ************************************************************************
> File Name:     LeetCode49.cpp
> Author:        niu0217
> Created Time:  五  2/16 12:45:06 2024
 ************************************************************************/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        //key;   排序后的单词
        //value: 该key对应的字母异位词
        unordered_map<string, vector<string>> umap;
        vector<vector<string>> result;
        for(auto s : strs) {
            string sortedS = s;
            sort(begin(sortedS), end(sortedS));
            umap[sortedS].push_back(s);
        }
        for(auto part : umap) {
            result.push_back(part.second);
        }
        return result;
    }
};
