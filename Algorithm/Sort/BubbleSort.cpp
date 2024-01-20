#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void bubbleSort(vector<int>& elements) {
    int elementsSize = elements.size();
    for(int i = 0; i < elementsSize; i++) {
        bool isSwaped = false;
        for(int j = 1; j < elementsSize - i; j++) {
            if(elements[j - 1] > elements[j]) {
                swap(elements[j - 1], elements[j]);
                isSwaped = true;
            }
        }
        if(!isSwaped) {
            break;
        }
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    bubbleSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
