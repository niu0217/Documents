# 字符串

## 反转字符串

## 反转字符串II

## 替换数字

## 翻转字符串中的单词

## 右旋转字符串

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

### 实现strStr()

### 重复的子字符串

