/* ************************************************************************
> File Name:     LeetCode454.cpp
> Author:        niu0217
> Created Time:  五  2/16 15:42:41 2024
 ************************************************************************/

class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        //key:   a+b的和
        //value: a+b的和的次数
        unordered_map<int, int> umap;
        for(int a : A) {
            for(int b : B) {
                umap[a+b]++;
            }
        }
        int count = 0;
        for(int c : C) {
            for(int d : D) {
                int target = 0 - (c + d);
                auto iter = umap.find(target);
                if(iter != umap.end()) {
                    count += iter->second;
                }
            }
        }
        return count;
    }
};
