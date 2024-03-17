# C++中的bitset

在C++中，`std::bitset` 是一个标准库中的模板类，用于表示固定长度的位序列。它提供了一种非常高效的方式来存储和操作位，类似于一个只包含 0 和 1 的固定长度的数组。

以下是一些`std::bitset`类的常见操作和特性：

## 创建 bitset 对象

你可以使用以下语法创建一个bitset对象：

```cpp
#include <bitset>

std::bitset<8> bits; // 创建包含 8 位的 bitset
```

## 初始化

你可以初始化 `std::bitset` 为特定的二进制值：

```cpp
std::bitset<4> bits1(0b0101); // 从二进制串初始化
std::bitset<8> bits2("10101111"); // 从字符串初始化
```

## 访问和修改位

你可以使用下标运算符来访问和修改位：

```cpp
bits[3] = 1; // 将第 3 位设置为1
bool bitValue = bits[6]; // 读取第 6 位的值
```

## 位操作

`std::bitset` 支持位操作，例如与、或、非、异或等操作：

```cpp
std::bitset<4> bits1(0b1010);
std::bitset<4> bits2(0b1100);

std::bitset<4> resultAND = bits1 & bits2; // 按位与
std::bitset<4> resultOR = bits1 | bits2; // 按位或
std::bitset<4> resultXOR = bits1 ^ bits2; // 按位异或
std::bitset<4> resultNOT = ~bits1; // 按位取反
```

## 其他常见操作

- `count()`: 返回置位(bit为1)的数量。
- `to_ulong()`,`to_ullong()`: 将bitset转换为对应的unsigned long或unsigned long long值。
- `set()`,`reset()`,`flip()`: 分别用于设置位为1、重置为0、翻转位的状态。

`std::bitset` 是一个非常方便且高效的工具，特别适用于涉及位操作的场景，比如 bit-level编程、密码学等领域。