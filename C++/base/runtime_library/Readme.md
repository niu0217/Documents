# 运行库

## 基础

任何一个C程序，它的背后都有一套庞大的代码来进行支撑，以使得该程序能够正常运行。这套代码至少包括入口函数，及其所依赖的函数所构成的函数集合。当然，它还理应包括各种标准库函数的实现。

这样的代码集合称之为运行时库（Runtime Library）。而C语言的运行库，被称为C运行库（CRT）。

一个C语言运行库大致包含以下功能：

+ 启动与退出：包括入口函数及入口函数所依赖的其他函数等。
+ 标准函数：由C语言标准规定的C语言标准库所拥有的函数实现。
+ IO：IO功能的封装与实现。
+ 堆：堆的封装与实现。
+ 语言实现：语言中一些特殊功能的实现。
+ 调试：实现调试功能的代码

## 实践

[自己实现C语言运行库.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/base/runtime_library/自己实现C语言运行库.md)

[自己实现C++运行库.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/base/runtime_library/自己实现C%2B%2B运行库.md)

## 标准库函数

[fread实现.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/base/runtime_library/fread实现.md)

