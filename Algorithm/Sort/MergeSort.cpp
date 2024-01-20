#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void merge(vector<int>& elements, int idxStart, int idxMid, int idxEnd) {
    vector<int> leftSubArray(begin(elements) + idxStart,
                             begin(elements) + idxMid + 1);
    vector<int> rightSubArray(begin(elements) + idxMid + 1,
                              begin(elements) + idxEnd + 1);
    leftSubArray.insert(end(leftSubArray), numeric_limits<int>::max());
    rightSubArray.insert(end(rightSubArray), numeric_limits<int>::max());
    int idxLeft = 0;
    int idxRight = 0;
    for(int i = idxStart; i <= idxEnd; i++) {
        if(leftSubArray[idxLeft] < rightSubArray[idxRight]) {
            elements[i] = leftSubArray[idxLeft];
            idxLeft++;
        }
        else {
            elements[i] = rightSubArray[idxRight];
            idxRight++;
        }
    }
}

void mergeSort(vector<int>& elements, int idxStart, int idxEnd) {
    if(idxStart >= idxEnd) {
        return;
    }
    int idxMid = idxStart + (idxEnd - idxStart) / 2;
    mergeSort(elements, idxStart, idxMid);
    mergeSort(elements, idxMid + 1, idxEnd);
    merge(elements, idxStart, idxMid, idxEnd);
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    int elementsSize = elements.size();
    mergeSort(elements, 0, elementsSize - 1);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
