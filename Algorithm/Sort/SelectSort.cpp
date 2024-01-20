#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void selectSort(vector<int>& elements) {
    int elementsSize = elements.size();
    for(int i = 0; i < elementsSize; i++) {
        int minValueIndex = i;
        for(int j = i + 1; j < elementsSize; j++) {
            if(elements[j] < elements[minValueIndex]) {
                minValueIndex = j;
            }
        }
        if(minValueIndex != i) {
            swap(elements[minValueIndex], elements[i]);
        }
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    selectSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
