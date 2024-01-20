#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void insertSort(vector<int>& elements) {
    int size = elements.size();
    for(int i = 1; i < size; i++) {
        for(int j = i; j > 0; j--) {
            if(elements[j - 1] > elements[j]) {
                swap(elements[j - 1], elements[j]);
            }
            else {
                break;
            }
        }
    }
}

int main()
{
    vector<int> elements = {
        1, 4, 7, 2, 5, 8
    };
    insertSort(elements);
    for(const auto& element : elements) {
        cout<<element<<" ";
    }
    cout<<endl;
}
