# vector

## 1. 问题

### 1.1 迭代器什么时候会失效？

C++中`std::vector`的迭代器可能会在以下情况下失效：

1. **向`std::vector`中添加元素导致其大小变化**： 当在`std::vector`的中间或头部插入元素时，可能会导致现有元素的移动。这会导致所有指向被移动元素的迭代器失效。

例如：

```c++
//测试迭代器失效
void test1() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin() + 2; // 指向元素3
    cout<<*it<<endl; //3 
    vec.insert(vec.begin(), 0); // 在头部插入元素0

    // 此时，it不再有效，因为元素3已经被移动到索引3的位置
    cout<<*it<<endl; //1574359056,证明迭代器以及失效了
}
```

2. **从`std::vector`中删除元素导致其大小变化**： 当在`std::vector`的中间或头部删除元素时，同样可能导致现有元素的移动。这也会导致所有指向被移动元素的迭代器失效。

例如：

```c++
void test2() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin() + 2; // 指向元素3
    cout<<*it<<endl; //3

    vec.erase(it); // 删除头部元素1

    // 此时，it不再有效，因为元素3已经被移动到索引2的位置
    cout<<*it<<endl; //4
}

//it指向的已经不是我们想要的值了，失效
```

3. **使用`std::vector`的`resize()`、`reserve()`、`shrink_to_fit()`等函数改变其容量**： 这些操作可能导致`std::vector`重新分配内存，从而使得所有现有的迭代器失效。

例如：

```c++
void test3() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin() + 2; // 指向元素3
    cout<<*it<<endl; //3

    vec.resize(10); // 扩大vector的大小

    // 此时，it不再有效，因为vector可能已经重新分配了内存
    cout<<*it<<endl; //907083792,失效
}
```

请注意，如果只是在`std::vector`的末尾添加或删除元素，且不触发容量调整，那么指向未受影响区域的迭代器通常会保持有效。但是，一旦涉及元素的移动或内存的重新分配，指向这些元素的迭代器就会失效。在使用迭代器时，应始终注意可能发生的这些情况，并在必要时更新迭代器以保持其有效性。

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

## 4. 优点和缺点

C++中的`std::vector`是一个动态数组容器，以下列出了其主要的优点和缺点：

**优点：**

1. **动态大小**： `std::vector`的大小可以在运行时动态改变，无需预先知道元素数量。
2. **连续内存存储**： 元素在内存中连续存储，支持随机访问，对于需要快速访问元素的场景非常高效。
3. **内存管理**： 自动处理内存分配和释放，简化了编程负担。
4. **容量管理**： 当向`std::vector`中添加元素导致容量不足时，它会自动重新分配更大的内存空间，并将原有元素移动到新的内存位置。同时，`std::vector`通常会预留一些额外的空间以减少频繁的内存重新分配操作。
5. **兼容性**： `std::vector`与标准库中的算法和其他容器高度兼容，可以方便地使用`<algorithm>`头文件中的各种算法对元素进行排序、搜索、遍历等操作。
6. **迭代器稳定性**： 在不改变`std::vector`大小的情况下（如在末尾插入或删除元素），迭代器保持有效。

**缺点：**

1. **插入和删除操作可能效率较低**： 在中间插入或删除元素时，可能导致大量元素移动，特别是在向头部插入元素时。
2. **内存碎片**： 随着元素的添加和删除，可能会导致内存碎片。
3. **迭代器失效**： 当向`std::vector`中添加或删除元素导致其大小变化时，指向受影响区域的迭代器可能会失效。
4. **预留空间可能导致内存浪费**： `std::vector`为了优化插入操作而预留的额外空间，在某些情况下可能会导致内存的浪费。
5. **不适用于固定大小的静态数据**： 如果元素数量在编译时就已经确定并且不需要在运行时改变大小，那么`std::array`可能是更优的选择，因为它没有额外的内存管理开销。

## 4. 增删查改的效率

**增删查改的算法效率：**

- **查找（线性搜索）**：线性时间复杂度O(n)。
- **修改（通过索引访问）**：常数时间复杂度O(1)。
- **增加（在末尾）**：常数时间复杂度O(1)，除非需要重新分配内存。
- **删除（在末尾）**：常数时间复杂度O(1)，除非需要收缩内存。
- **增加（在中间）**：线性时间复杂度O(n)，因为可能需要移动后续元素。
- **删除（在中间）**：线性时间复杂度O(n)，因为可能需要移动后续元素。

总的来说，`std::vector`是一个灵活、高效且易于使用的容器，特别适合于那些需要动态调整大小并且能够容忍在中间插入或删除元素时可能产生的效率损失的场景。然而，如果需要频繁在中间插入或删除元素或者对内存效率有较高要求的场景，可能需要考虑使用其他数据结构，如`std::list`或`std::deque`。

## 5. 资料解释vector实现原理

https://c.biancheng.net/view/6901.html

## 6. 补充

### 6.1 在中间插入元素

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 确定要插入元素的位置
    int insert_index = 2; // 在索引为2的位置插入元素

    // 要插入的元素
    int new_element = 10;

    // 在指定位置插入元素
    vec.insert(vec.begin() + insert_index, new_element);

    // 打印修改后的vector
    for (const auto &value : vec) {
        std::cout << value << ' ';
    }

    return 0;
}
```

### 6.2 在中间删除元素

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 确定要删除元素的位置
    int delete_index = 2; // 删除索引为2的元素

    // 删除指定位置的元素
    vec.erase(vec.begin() + delete_index);

    // 打印修改后的vector
    for (const auto &value : vec) {
        std::cout << value << ' ';
    }

    return 0;
}
```

### 6.3 查找中间的元素

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    int target = 3; // 要查找的元素

    // 初始化一个迭代器用于遍历vector
    auto it = vec.begin();

    // 遍历vector，查找目标元素
    while (it != vec.end()) {
        if (*it == target) {
            std::cout << "Found element " << target << " in the vector." << std::endl;
            return 0;
        }
        ++it;
    }

    std::cout << "Element " << target << " not found in the vector." << std::endl;

    return 0;
}
```

### 6.4 修改中间的元素

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    int target = 3; // 要修改的元素的当前值
    int new_value = 12; // 要修改的元素的新值

    // 初始化一个迭代器用于遍历vector
    auto it = vec.begin();

    // 遍历vector，查找要修改的元素
    while (it != vec.end()) {
        if (*it == target) {
            *it = new_value; // 更新元素的值
            std::cout << "Element " << target << " has been modified to " << new_value << " in the vector." << std::endl;
            return 0;
        }
        ++it;
    }

    std::cout << "Element " << target << " not found in the vector." << std::endl;

    return 0;
}
```