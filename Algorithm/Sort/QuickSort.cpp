#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int partition(vector<int>& elements, int low, int high) {
    int pivot = elements[low];
    while(low < high) {
        //从右边找第一个小于pivot的数的位置
        while(low < high && elements[high] >= pivot) {
            high--;
        }
        if(low < high) {
            elements[low] = elements[high];
        }
        //从左边找第一个大于pivot的数的位置
        while(low < high && elements[low] <= pivot) {
            low++;
        }
        if(low < high) {
            elements[high] = elements[low];
        }
    }
    elements[low] = pivot;
    return low;
}

void quickSort(vector<int>& elements, int low, int high) {
    if(low < high) {
        int pivot = partition(elements, low, high);
        quickSort(elements, low, pivot - 1);
        quickSort(elements, pivot + 1, high);
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    int elementsSize = elements.size();
    quickSort(elements, 0, elementsSize - 1);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
