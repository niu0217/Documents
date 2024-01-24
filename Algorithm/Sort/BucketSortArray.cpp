#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

void bucketSort(vector<int>& arr) {
    vector<vector<int>> bucketArray(5, vector<int>(5, INT_MAX));
    vector<int> bucketSizeArray(5, 0);
    int arrSize = arr.size();
    for(int i = 0; i < arrSize; i++) {
        bucketArray[arr[i] / 10][bucketSizeArray[arr[i] / 10]++] = arr[i];
    }
    for(int i = 0; i < 5; i++) {
        sort(begin(bucketArray[i]), end(bucketArray[i]));
    }
    int k = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < bucketSizeArray[i]; j++) {
            arr[k++] = bucketArray[i][j];
        }
    }
}

int main()
{
    vector<int> arr = {
        21, 3, 30, 44, 15, 36, 6, 10, 9, 19, 25, 48, 5, 23, 47
    };
    bucketSort(arr);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}

