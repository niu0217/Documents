# vector

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <vector>

// 自定义类，用于演示向vector中添加对象
class MyClass {
public:
    MyClass(int value) : value_(value) {}
    int getValue() const { return value_; }
private:
    int value_;
};

int main() {
    // 创建一个空的vector
    std::vector<int> intVector;

    // 在vector末尾添加元素
    intVector.push_back(10);
    intVector.push_back(20);
    intVector.push_back(30);

    // 使用emplace_back在vector末尾创建并添加元素
    intVector.emplace_back(40);

    // 在vector开头添加元素
    intVector.insert(intVector.begin(), 0);

    // 在vector中间插入元素
    intVector.insert(intVector.begin() + 2, 25);

    // 删除元素
    intVector.erase(intVector.begin() + 1);

    // 访问元素
    std::cout << "Element at index 0: " << intVector[0] << std::endl;
    std::cout << "Element at index 1: " << intVector[1] << std::endl;
    std::cout << "Element at index 2: " << intVector[2] << std::endl;

    // 修改元素
    intVector[0] = 5;
    std::cout << "After modification, element at index 0: " << intVector[0] << std::endl;

    // 获取vector的大小
    std::size_t vectorSize = intVector.size();
    std::cout << "Size of the vector: " << vectorSize << std::endl;

    // 检查vector是否为空
    if (intVector.empty()) {
        std::cout << "Vector is empty." << std::endl;
    } else {
        std::cout << "Vector is not empty." << std::endl;
    }

    // 清空vector
    intVector.clear();

    // 使用范围for循环遍历vector
    for (const auto& element : intVector) {
        std::cout << "Element: " << element << std::endl;
    }

    // 使用begin()和end()进行迭代
    for (auto it = intVector.begin(); it != intVector.end(); ++it) {
        std::cout << "Element: " << *it << std::endl;
    }

    // 向vector中添加自定义对象
    std::vector<MyClass> objVector;
    objVector.push_back(MyClass(50));
    objVector.push_back(MyClass(60));

    // 访问自定义对象的值
    for (const auto& obj : objVector) {
        std::cout << "Object value: " << obj.getValue() << std::endl;
    }

    return 0;
}
```

## 3. 简单叙述原理

C++中的`std::vector`是一种动态数组容器，其内部实现原理主要包括以下几个关键部分：

1. **连续内存存储**： `std::vector`的元素在内存中是连续存储的，这使得它可以像普通数组一样通过索引快速访问元素。这种特性使得`std::vector`非常适合需要频繁随机访问元素的场景。
2. **动态容量管理**： `std::vector`的容量（capacity）是可以动态改变的。当向`std::vector`中添加元素时，如果当前容量不足以容纳新元素，`std::vector`会自动重新分配更大的内存空间，并将原有元素移动到新的内存位置。
3. **预留空间**： 为了减少频繁的内存重新分配操作，`std::vector`在实际分配内存时通常会预留一些额外的空间。当向`vector`中添加元素导致容量不足时，`vector`会一次性分配比当前所需大小更多的内存，以备后续添加元素。
4. **迭代器和指针**： `std::vector`提供了迭代器（iterator）和指向元素的指针来访问和操作元素。由于元素在内存中是连续存储的，所以`std::vector`的迭代器支持随机访问迭代器的概念，可以使用类似`v[i]`的方式访问元素。
5. **数据结构**： 在内部，`std::vector`通常包含以下三个主要成员变量：
   - `_M_start` 或 `_Myfirst`：指向第一个元素的指针。
   - `_M_finish` 或 `_Mylast`：指向最后一个元素之后的位置的指针。
   - `_M_end_of_storage` 或 `_Myend`：指向已分配内存末尾的指针。
6. **内存分配和释放**： 当需要增加容量时，`std::vector`会调用内存分配函数（如`::operator new[]()`）分配更大的内存块，然后将原有元素复制或移动到新内存位置。当容量减少或者`std::vector`被销毁时，会调用内存释放函数（如`::operator delete[]()`）释放不再需要的内存。
7. **构造、赋值和析构**： `std::vector`提供了多种构造函数，包括默认构造函数、范围构造函数、填充构造函数等。它还支持赋值操作符和析构函数，用于正确地初始化、复制和清理`vector`对象。
8. **算法支持**： `std::vector`与标准库中的算法高度兼容，可以方便地使用`<algorithm>`头文件中的各种算法对元素进行排序、搜索、遍历等操作。

总的来说，`std::vector`的实现原理结合了连续内存存储、动态容量管理和高效的数据访问机制，使其成为一种灵活、高效且易于使用的容器。