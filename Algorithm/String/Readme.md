# 字符串

## 反转字符串

[LeetCode344.cpp](https://github.com/niu0217/Documents/blob/main/Algorithm/String/LeetCode344.cpp)

## 反转字符串II

[LeetCode541.cpp](https://github.com/niu0217/Documents/blob/main/Algorithm/String/LeetCode541.cpp)

## 替换数字

```c++
#include<iostream>
using namespace std;
int main() {
    string s;
    while (cin >> s) {
        int count = 0; // 统计数字的个数
        int sOldSize = s.size();
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                count++;
            }
        }
        // 扩充字符串s的大小，也就是每个空格替换成"number"之后的大小
        s.resize(s.size() + count * 5);
        int sNewSize = s.size();
        // 从后先前将空格替换为"number"
        for (int i = sNewSize - 1, j = sOldSize - 1; j < i; i--, j--) {
            if (s[j] > '9' || s[j] < '0') {
                s[i] = s[j];
            } else {
                s[i] = 'r';
                s[i - 1] = 'e';
                s[i - 2] = 'b';
                s[i - 3] = 'm';
                s[i - 4] = 'u';
                s[i - 5] = 'n';
                i -= 5;
            }
        }
        cout << s << endl;
    }
}
```

## 翻转字符串中的单词

[LeetCode151.cpp](https://github.com/niu0217/Documents/blob/main/Algorithm/String/LeetCode151.cpp)

## 右旋转字符串

```c++
// 版本一
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;
    int len = s.size(); //获取长度

    reverse(s.begin(), s.end()); // 整体反转
    reverse(s.begin(), s.begin() + n); // 先反转前一段，长度n
    reverse(s.begin() + n, s.end()); // 再反转后一段

    cout << s << endl;

} 
```

## KMP

### 解释KMP

举例：aabaaf

前缀：包含首字母，不包含尾字母的所有子串。

+ a
+ aa
+ aab
+ aaba
+ aabaa

后缀：不包含首字母，包含尾字母的所有子串。

+ f
+ af
+ aaf
+ baaf
+ abaaf

最长相等前后缀：

+ a
  + 无前缀
  + 无后缀
  + 相同长度0
+ aa
  + 前缀：a
  + 后缀：a
  + 相同长度1
+ aab
  + 前缀：a、aa
  + 后缀：b、ab
  + 相同长度0
+ aaba
  + 前缀：a、aa、aab
  + 后缀：a、ba、aba
  + 相同长度1
+ aabaa
  + 前缀：a、aa、aab、aaba
  + 后缀：a、aa、baa、abaa
  + 相同长度2
+ aabaaf
  + 前缀：a、aa、aab、aaba、aabaa
  + 后缀：f、af、aaf、baaf、abaaf
  + 相同长度0

### 找出字符串中第一个匹配项的下标

[LeetCode28.cpp](https://github.com/niu0217/Documents/blob/main/Algorithm/String/LeetCode28.cpp)

### 重复的子字符串

[LeetCode459.cpp](https://github.com/niu0217/Documents/blob/main/Algorithm/String/LeetCode459.cpp)