/* ************************************************************************
> File Name:     LeetCode454.cpp
> Author:        niu0217
> Created Time:  五  2/16 15:42:41 2024
 ************************************************************************/

class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        //key:   a+b的和
        //value: a+b的和出现的次数
        unordered_map<int, int> umap;
        for(int a : A) {
            for(int b : B) {
                umap[a + b]++;
            }
        }
        int count = 0; //统计a+b+c+d出现的次数
        for(int c : C) {
            for(int d : D) {
                if(umap.find(0 - (c + d)) != umap.end()) {
                    count += umap[0 - (c + d)];
                }
            }
        }
        return count;
    }
};
