# array

## 1. 问题

## 2. 引入代码

```c++
#include <array>
#include <iostream>

// 定义一个包含3个整数的std::array
std::array<int, 3> myArray = {10, 20, 30};

int main() {
    printf("*************访问元素*****************************\n");
    std::cout << "Element at index 0: " << myArray[0] << std::endl;
    std::cout << "Element at index 1: " << myArray[1] << std::endl;
    std::cout << "Element at index 2: " << myArray[2] << std::endl;
    std::cout << "Element at index 0: " << myArray.front() << std::endl;
    std::cout << "Element at index 2: " << myArray.back() << std::endl;
    std::cout << "Element at index 2: " << myArray.at(2) << std::endl;
    std::cout << "Element at index 2: " << std::get<2>(myArray) << std::endl;
    printf("\n\n");

    printf("***********取得array数组的第一个元素地址***********\n");
    std::cout << "Element at index 0: " << myArray.data() << std::endl;
    std::cout << "Element at index 0: " << &myArray[0] << std::endl;
    std::cout << "Element at index 0: " << &myArray.at(0) << std::endl;
    printf("\n\n");

    printf("***********修改元素***********\n");
    myArray[0] = 5;
    std::cout << "After modification, element at index 0: " << myArray[0] << std::endl;
    printf("\n\n");

    printf("***********获取数组的大小***********\n");
    std::size_t arraySize = myArray.size();
    std::cout << "Size of the array: " << arraySize << std::endl;
    printf("\n\n");

    printf("***********使用范围for循环遍历数组***********\n");
    for (const auto& element : myArray) {
        std::cout << "Element: " << element << std::endl;
    }
    printf("\n\n");

    printf("***********使用begin()和end()进行迭代***********\n");
    for (auto it = myArray.begin(); it != myArray.end(); ++it) {
        std::cout << "Element: " << *it << std::endl;
    }
    printf("\n\n");

    return 0;
}
```

## 3. 简单叙述原理

C++中的`std::array`是一个固定大小的数组容器，它是C++标准库的一部分。以下是`std::array`的一些基本原理：

1. **固定大小**： `std::array`的大小在编译时就必须确定，并且不能改变。这意味着你必须在定义`std::array`时指定元素的数量。
2. **连续内存存储**： `std::array`的元素在内存中是连续存储的，这与C++的内置数组相似。这种特性使得可以通过索引快速访问元素，类似于使用指针进行偏移。
3. **数据结构**： 在内部，`std::array`通常包含一个固定大小的元素数组和一些元数据。由于其大小是固定的，所以不需要像`std::vector`那样维护额外的容量信息。
4. **元素访问**： `std::array`提供了下标操作符（`operator[]`）来访问和修改元素，其行为与内置数组的下标操作符类似。
5. **类型安全**： `std::array`是类型安全的，它的大小是类型的一部分。这意味着不同大小的`std::array`被视为不同的类型，这有助于防止运行时错误。
6. **兼容性**： `std::array`与标准库中的算法和其他容器高度兼容，可以方便地使用`<algorithm>`头文件中的各种算法对元素进行排序、搜索、遍历等操作。
7. **内存管理**： 由于`std::array`的大小是固定的，因此不需要动态分配或释放内存。这使得`std::array`在内存管理方面比`std::vector`更简单，但也限制了其在需要动态调整大小的场景中的应用。
8. **效率**： 由于元素在内存中是连续存储的，`std::array`支持随机访问，对于需要快速访问元素的场景非常高效。然而，插入和删除元素的操作在`std::array`中通常是不被支持的，因为其大小是固定的。

总的来说，`std::array`的原理是提供一个固定大小、类型安全且内存管理简单的数组容器，适用于元素数量在编译时就已经确定并且不需要在运行时改变大小的情况。它的设计目标是在保持与内置数组类似的性能优势的同时，提供更好的类型安全性和与其他C++标准库组件的兼容性。

## 4. 优点和缺点

`std::array`是C++标准库中的一种固定大小的数组容器，以下列出了其优点和缺点，以及增删查改操作的效率：

**优点：**

1. **性能**： 由于元素在内存中连续存储，`std::array`支持随机访问，访问元素的时间复杂度为O(1)，与内置数组一样高效。
2. **类型安全**： `std::array`的大小是类型的一部分，这使得不同大小的`std::array`被视为不同的类型，增强了类型安全性。
3. **内存管理**： 由于`std::array`的大小是固定的，不需要动态分配或释放内存，减少了内存管理的开销。
4. **兼容性**： `std::array`与标准库中的算法和其他容器高度兼容，可以方便地使用`<algorithm>`头文件中的各种算法对元素进行排序、搜索、遍历等操作。
5. **空间效率**： 相比于`std::vector`，`std::array`没有额外的内存开销用于存储容量信息和管理指针。

**缺点：**

1. **固定大小**： `std::array`的大小在编译时就必须确定，并且不能改变。这意味着你无法在运行时向数组中添加或删除元素。
2. **不适用于动态数据**： 如果你的元素数量在运行时可能会改变，那么`std::array`不是一个合适的选择，因为它的大小是固定的。
3. **插入和删除操作**： `std::array`不直接支持插入和删除操作。如果需要在数组中插入或删除元素，你需要手动移动后续元素，这可能效率较低。

## 5. 增删查改效率

- **查找（线性搜索）**：线性时间复杂度O(n)。
- **修改（通过索引访问）**：常数时间复杂度O(1)。



