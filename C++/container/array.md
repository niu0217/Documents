# array

## 1. 问题

## 2. 引入代码

```c++
#include <array>
#include <iostream>

// 定义一个包含3个整数的std::array
std::array<int, 3> myArray = {10, 20, 30};

int main() {
    // 访问元素
    std::cout << "Element at index 0: " << myArray[0] << std::endl;
    std::cout << "Element at index 1: " << myArray[1] << std::endl;
    std::cout << "Element at index 2: " << myArray[2] << std::endl;

    // 修改元素
    myArray[0] = 5;
    std::cout << "After modification, element at index 0: " << myArray[0] << std::endl;

    // 获取数组的大小
    std::size_t arraySize = myArray.size();
    std::cout << "Size of the array: " << arraySize << std::endl;

    // 使用范围for循环遍历数组
    for (const auto& element : myArray) {
        std::cout << "Element: " << element << std::endl;
    }

    // 使用begin()和end()进行迭代
    for (auto it = myArray.begin(); it != myArray.end(); ++it) {
        std::cout << "Element: " << *it << std::endl;
    }

    return 0;
}
```

