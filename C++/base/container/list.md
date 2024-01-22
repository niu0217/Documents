# list

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <list>
#include <algorithm>

// 自定义类，用于演示向list中添加对象
class MyClass {
public:
    MyClass(int value) : value_(value) {}
    int getValue() const { return value_; }
private:
    int value_;
};

int main() {
    // 创建一个空的list
    std::list<int> intList;

    // 在list末尾添加元素
    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);

    // 在list开头添加元素
    intList.push_front(0);

    // 在list中间插入元素
    auto it = intList.begin();
    std::advance(it, 2); // 移动迭代器到索引2的位置
    intList.insert(it, 25);

    // 删除元素
    it = intList.begin();
    std::advance(it, 1); // 移动迭代器到索引1的位置
    intList.erase(it);

    // 访问元素
    std::cout << "Element at front: " << intList.front() << std::endl;
    std::cout << "Element at back: " << intList.back() << std::endl;

    // 修改元素
    it = intList.begin();
    *it = 5;
    std::cout << "After modification, element at front: " << intList.front() << std::endl;

    // 获取list的大小
    std::size_t listSize = intList.size();
    std::cout << "Size of the list: " << listSize << std::endl;

    // 检查list是否为空
    if (intList.empty()) {
        std::cout << "List is empty." << std::endl;
    } else {
        std::cout << "List is not empty." << std::endl;
    }


    // 使用范围for循环遍历list
    for (const auto& element : intList) {
        std::cout << "Element: " << element << std::endl;
    }

    // 使用begin()和end()进行迭代
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << "Element: " << *it << std::endl;
    }

    // 向list中添加自定义对象
    std::list<MyClass> objList;
    objList.push_back(MyClass(50));
    objList.push_back(MyClass(60));

    // 访问自定义对象的值
    for (const auto& obj : objList) {
        std::cout << "Object value: " << obj.getValue() << std::endl;
    }

    // 删除满足条件的元素
    it = std::remove_if(intList.begin(), intList.end(), [](int i) { return i % 2 == 0; });
    intList.erase(it, intList.end());

    // 清空list
    intList.clear();

    return 0;
}
```

## 3. 基本实现原理

C++标准库中的`std::list`是一种双向链表容器。其基本实现原理如下：

1. **节点结构**： `std::list`的内部实现基于节点（Node）的概念。每个节点包含两个指针，分别指向前一个和后一个节点。节点中还存储了实际的数据元素。
2. **头尾指针**： `std::list`容器维护两个指针，一个指向链表的头部（第一个元素），另一个指向链表的尾部（最后一个元素）。这样可以快速地在链表的两端进行插入和删除操作。
3. **动态内存管理**： 当向`std::list`中添加或删除元素时，会动态地分配或释放节点所需的内存。这通常通过使用`new`和`delete`运算符来完成。
4. **迭代器**： `std::list`提供了迭代器（iterator）来访问和遍历链表中的元素。迭代器实际上是一个指向节点的指针，通过迭代器可以访问节点中的数据元素以及前一个和后一个节点。
5. **插入和删除操作**： 在双向链表中，插入和删除操作相对高效。插入操作只需要修改相邻节点的指针即可，而删除操作则需要更新被删除节点的前一个和后一个节点的指针以保持链表的连续性。
6. **顺序访问**： 虽然`std::list`支持高效的插入和删除操作，但是由于其数据结构特性，随机访问（通过索引直接访问某个元素）的效率较低。要访问列表中的特定元素，需要从头或尾部开始逐个遍历节点。

以下是一个简化的`std::list`内部节点结构的示例：

```c++
template <typename T>
struct ListNode {
    T data; // 存储元素数据
    ListNode* prev; // 指向前一个节点的指针
    ListNode* next; // 指向后一个节点的指针

    ListNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};
```

实际的`std::list`实现会更复杂，包括额外的优化和错误检查等。但以上描述涵盖了`std::list`的基本实现原理。

## 4. 优点和缺点

C++中的`std::list`是一种双向链表容器，具有以下优点和缺点：

**优点：**

1. **高效的插入和删除操作**： `std::list`在任何位置（包括中间）插入和删除元素的时间复杂度都是O(1)，这是因为只需要修改相邻节点的指针即可。
2. **迭代器稳定性**： 当在`std::list`中添加或删除元素时，只要不删除迭代器所指向的元素，迭代器就会保持有效。这使得在遍历列表的同时进行元素的修改成为可能。
3. **内存分配**： `std::list`的元素存储是离散的，每个元素都有自己的内存空间。这意味着插入和删除操作不会导致大量元素的移动，从而减少了内存碎片。
4. **动态大小**： `std::list`的大小可以在运行时动态改变，无需预先知道元素数量。

**缺点：**

1. **随机访问效率低**： 由于`std::list`的数据结构特性，通过索引直接访问某个元素（随机访问）的效率较低，时间复杂度为O(n)。
2. **额外的空间开销**： 每个元素都需要存储前一个和后一个节点的指针，这导致了额外的空间开销。
3. **代码复杂性**： 使用`std::list`可能需要更复杂的代码来处理迭代器和节点之间的关系，相比其他容器如`std::vector`，其接口可能不太直观。
4. **顺序访问效率相对较低**： 虽然`std::list`支持高效的插入和删除操作，但顺序访问（从头到尾或从尾到头）的效率相比连续存储的容器（如`std::vector`）较低。

总的来说，`std::list`适合于那些需要频繁插入和删除元素，且不需要随机访问的场景。如果程序主要依赖于快速随机访问或者对内存效率有较高要求，那么其他容器如`std::vector`或`std::deque`可能会是更好的选择。

## 5. 增删查改的效率

C++中的`std::list`是一种双向链表容器，其增删查改的效率如下：

**插入（Insertion）：**

- 在列表的任何位置（包括头部和尾部）插入元素的时间复杂度为O(1)。这是因为双向链表只需要修改相邻节点的指针即可完成插入操作。

**删除（Deletion）：**

- 从列表的任何位置（包括头部和尾部）删除元素的时间复杂度也为O(1)。同样，只需修改相邻节点的指针即可完成删除操作。

**查找（Search）：**

- 查找特定元素在列表中的位置（通过迭代器）的时间复杂度为O(n)，其中n是列表中元素的数量。因为双向链表不支持随机访问，所以需要从头或尾开始逐个遍历元素来查找目标。

**修改（Modification）：**

- 修改列表中已存在的元素的时间复杂度取决于你如何获取到该元素的引用。如果已经有一个指向该元素的迭代器，那么修改操作的时间复杂度为O(1)。但如果需要先查找元素，那么总时间复杂度将是查找操作的O(n)加上修改操作的O(1)。

总结起来，`std::list`在插入和删除操作上具有高效的O(1)时间复杂度，但在查找和某些情况下的修改操作上效率较低，时间复杂度为O(n)。因此，`std::list`适用于那些需要频繁进行插入和删除操作，但对查找和修改操作速度要求不高的场景。如果程序中主要依赖于快速查找或者随机访问元素，那么其他容器如`std::vector`或`std::unordered_map`可能会是更好的选择。

## 6. 补充

### 6.1 在中间插入代码

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 确定要插入元素的位置
    auto insert_position = lst.begin();
    for (int i = 0; i < 2; ++i) {
        insert_position++;
    } // 现在，insert_position指向索引为2的位置

    // 要插入的元素
    int new_element = 10;

    // 在指定位置插入元素
    lst.insert(insert_position, new_element);

    // 打印修改后的list
    for (const auto &value : lst) {
        std::cout << value << ' ';
    }

    return 0;
}
```

### 6.2 在中间删除代码

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 确定要删除元素的位置
    auto delete_position = lst.begin();
    for (int i = 0; i < 2; ++i) {
        delete_position++;
    } // 现在，delete_position指向索引为2的位置

    // 删除指定位置的元素
    lst.erase(delete_position);

    // 打印修改后的list
    for (const auto &value : lst) {
        std::cout << value << ' ';
    }

    return 0;
}
```

### 6.3 查找中间的代码

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    int target = 3; // 要查找的元素

    // 初始化一个迭代器用于遍历list
    auto it = lst.begin();

    // 遍历list，查找目标元素
    while (it != lst.end()) {
        if (*it == target) {
            std::cout << "Found element " << target << " in the list." << std::endl;
            return 0;
        }
        ++it;
    }

    std::cout << "Element " << target << " not found in the list." << std::endl;

    return 0;
}
```

### 6.4 修改中间的代码

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    int target = 3; // 要修改的元素的当前值
    int new_value = 10; // 要修改的元素的新值

    // 初始化一个迭代器用于遍历list
    auto it = lst.begin();

    // 遍历list，查找要修改的元素
    while (it != lst.end()) {
        if (*it == target) {
            *it = new_value; // 更新元素的值
            std::cout << "Element " << target << " has been modified to " << new_value << " in the list." << std::endl;
            return 0;
        }
        ++it;
    }

    std::cout << "Element " << target << " not found in the list." << std::endl;

    return 0;
}
```

