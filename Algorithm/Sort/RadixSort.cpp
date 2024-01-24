#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

int maxbit(vector<int>& arr) {
    int size = arr.size();
    int maxData = arr[0];
    for(int i = 1; i < size; i++) {
        if(maxData < arr[i]) {
            maxData = arr[i];
        }
    }
    int d = 1;
    while(maxData >= 10) {
        maxData /= 10;
        ++d;
    }
    return d;
}

void countSort(vector<int>& arr, int maxVal, int radix) {
    int arrSize = arr.size();
    if(arrSize < 1) {
        return;
    }
    vector<int> counts(maxVal + 1, 0);
    vector<int> tempArr(arr);
    int k = 0;
    for(int j = 0; j < arrSize; j++) {
        k = (arr[j] / radix) % 10;
        counts[k]++;
    }
    for(int j = 1; j < 10; j++) {
        counts[j] += counts[j - 1];
    }
    for(int j = arrSize - 1; j >= 0; j--) {
        k = (tempArr[j] / radix) % 10;
        arr[counts[k] - 1] = tempArr[j];
        counts[k]--;
    }
}

void radixSort(vector<int>& arr) {
    int d = maxbit(arr);
    int radix = 1;
    for(int i = 1; i <= d; i++) {
        countSort(arr, 9, radix);
        radix = radix * 10;
    }
}

int main()
{
    vector<int> arr = {
        21, 3, 30, 44, 15, 36, 6, 10, 9, 19, 25, 48, 5, 23, 47
    };
    radixSort(arr);
    for(auto element : arr) {
        cout<<element<<" ";
    }
    cout<<endl;
}
