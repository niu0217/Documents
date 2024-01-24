#include<iostream>
#include<vector>
#include<string>
using namespace std;

void countSort(vector<int>& arr, int maxVal) {
    int size = arr.size();
    if(size < 1) {
        return;
    }
    vector<int> count(maxVal + 1, 0);
    vector<int> temp(arr);
    for(auto element : arr) {
        count[element]++;
    }
    for(int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }
    for(int i = size - 1; i >= 0; i--) {
        arr[count[temp[i]] - 1] = temp[i];
        count[temp[i]]--;
    }
}

int main()
{
    vector<int> arr = {
        1, 5, 3, 7, 6, 2, 8, 9, 4, 3, 3
    };
    int maxVal = 9;
    countSort(arr, maxVal);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}

