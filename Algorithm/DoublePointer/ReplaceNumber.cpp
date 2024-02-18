/* ************************************************************************
> File Name:     ReplaceNumber.cpp
> Author:        niu0217
> Created Time:  日  2/18 13:24:27 2024
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main()
{
    string s;
    while(cin>>s) {
        int count = 0;
        for(char ch : s) {
            if(ch >= '0' && ch <= '9') {
                count++;
            }
        }
        int sOldSize = s.size();
        s.resize(sOldSize + 5 * count);
        int sNewSize = s.size();
        int left = sOldSize - 1;
        int right = sNewSize - 1;
        while(left >= 0) {
            if(s[left] >= '0' && s[left] <= '9') {
                s[right] = 'r';
                s[right - 1] = 'e';
                s[right - 2] = 'b';
                s[right - 3] = 'm';
                s[right - 4] = 'u';
                s[right - 5] = 'n';
                right -= 5;
            }
            else {
                s[right] = s[left];
            }
            left--;
            right--;
        }
        cout<<s<<endl;
    }
}
