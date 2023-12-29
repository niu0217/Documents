# deque

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <deque>

int main() {
    // 创建一个 deque 容器
    std::deque<int> deq;

    // 向 deque 中添加元素
    deq.push_back(1);
    deq.push_front(2);
    deq.push_back(10);
    deq.push_back(20);
    deq.push_back(30);
    deq.insert(deq.begin() + 1, 3); // 在索引为1的位置插入元素

    // 打印 deque 的内容
    std::cout << "Deque contents: ";
    for (const auto &value : deq) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 删除 deque 中的元素
    deq.pop_back();
    deq.pop_front();
    deq.erase(deq.begin() + 1);

    // 访问 deque 中的元素
    std::cout << "First element: " << deq.front() << std::endl;
    std::cout << "Last element: " << deq.back() << std::endl;

    // 检查 deque 是否为空
    if (deq.empty()) {
        std::cout << "Deque is empty." << std::endl;
    } else {
        std::cout << "Deque is not empty." << std::endl;
    }

    // 获取 deque 的大小
    std::cout << "Size of deque: " << deq.size() << std::endl;

    // 清空 deque
    deq.clear();

    return 0;
}
```

这个示例代码中包含了以下操作：

- 创建 `deque` 容器
- 使用 `push_back` 和 `push_front` 添加元素到 deque 的末尾和开头
- 使用 `insert` 在指定位置插入元素
- 使用范围for循环遍历并打印 deque 的内容
- 使用 `pop_back`、`pop_front` 和 `erase` 删除元素
- 使用 `front` 和 `back` 访问 deque 的首尾元素
- 使用 `empty` 检查 deque 是否为空
- 使用 `size` 获取 deque 的大小
- 使用 `clear` 清空 deque

## 3. 原理

### 3.1 基本原理

C++中的`deque`（双端队列）是一种序列容器，它允许在两端进行高效插入和删除操作。以下是对`deque`原理解析的几个关键点：

1. 数据结构：
   - `deque`内部采用了一种混合数据结构，结合了数组和链表的优点。
   - 它由多个固定大小的连续内存块（也称为缓冲区或区块）组成，每个内存块可以存储一定数量的元素。
   - 每个内存块都有一个前向指针指向下一个内存块，形成一个双向链表。
2. 动态扩展：
   - 当需要在`deque`的前端或后端添加元素，而当前内存块没有足够的空间时，`deque`会在适当的位置动态地分配一个新的内存块，并将其链接到现有的链表中。
   - 这样做的好处是可以在常数时间内完成插入和删除操作，因为不需要移动其他元素。
3. 随机访问：
   - 虽然`deque`的底层是由多个连续内存块组成的，但是它提供了一个抽象接口，使得用户可以像使用单个连续数组一样对元素进行随机访问。
   - 这是通过维护一个映射（通常是一个指针数组）来实现的，该映射将元素的逻辑位置（索引）映射到其在物理内存中的实际位置。
4. 迭代器：
   - `deque`的迭代器是一种复杂的结构，因为它需要处理多个连续内存块的情况。
   - 迭代器包含了指向当前元素所在内存块的信息以及在该内存块内的偏移量。
   - 迭代器的操作（如递增和递减）需要考虑跨越内存块边界的情况。
5. 效率：
   - `deque`在头部和尾部插入和删除元素的时间复杂度为O(1)，这是因为这些操作只需要修改相邻内存块之间的链接关系或者在空闲内存块中添加或删除元素。
   - 随机访问元素的时间复杂度为O(1)，但需要注意的是，如果元素跨越了内存块边界，可能需要额外的时间来计算实际的物理位置。
6. 内存管理：
   - `deque`通过预先分配一些额外的内存块来减少动态分配的频率，这有助于提高性能。
   - 当不再需要某些内存块时，`deque`会释放它们以避免内存泄漏。

总的来说，`deque`通过结合数组和链表的优势，实现了在两端高效插入和删除、随机访问以及良好的内存管理。它的设计目标是在保持灵活性的同时，提供类似于数组的高性能操作。

### 3.2 资料补充

https://c.biancheng.net/view/6908.html

## 4. 优点和缺点

C++ 中 deque（双端队列）的优点主要包括：

**优点：**

1. 双向操作：deque 支持在头部和尾部高效地插入和删除元素，这使得它非常适合用作队列或者堆栈的数据结构。
2. 动态增长：与 vector 类似，deque 也是动态增长的容器，不需要预先知道元素的数量。
3. 连续空间：虽然内部实现是由多个连续的内存块组成，但对外提供的接口是连续的线性空间，方便进行随机访问。
4. 空间效率：由于其内部结构的特点，deque 在进行元素插入和删除时，不需要像 vector 那样移动大量元素。
5. 应用广泛：deque 可用于多种场景，包括处理需要频繁添加或删除元素的算法，如滑动窗口、队列操作等。

**缺点：**

1. 内存分配：虽然 deque 的动态增长可以避免一次性申请大量内存，但每次增加新的内存段都需要进行内存分配，可能会引入一定的开销。
2. 内部碎片：由于 deque 是由多个连续的内存块组成的，如果元素的插入和删除操作不均匀，可能导致内部出现碎片，降低空间利用率。
3. 随机访问：虽然 deque 提供了随机访问的能力，但相比 vector，其内部结构可能导致随机访问的效率略低，尤其是在需要跨越多个内存段的情况下。
4. 不适合缓存优化：deque 的多段内存结构可能不利于缓存局部性，影响性能。
5. 复杂性：deque 的内部实现相对复杂，理解和维护 deque 相关的代码可能需要更高的技术水平。

## 5. 增删查改的效率

在 C++ 中，deque（双端队列）的增删查改效率大致如下：

1. 增加（插入）：

   - 尾部插入（push_back）：效率高。deque 在尾部插入元素的操作通常非常快，因为它只需要在内部数组的末尾添加新元素。

   - 头部插入（push_front）：效率也相对较高。虽然不像尾部插入那样直接，但 deque 的设计允许它在头部高效地插入元素，因为它的内部结构支持在两端进行操作。

   - 中间插入（insert）：deque 在中间插入元素的效率不如其在头部和尾部的插入操作。当在 deque 中间插入元素时，需要移动后续元素以腾出空间，这可能导致 O(n) 的时间复杂度，其中 n 是被插入位置之后的元素数量。

     ```
     与删除操作类似，deque 的内部实现是由多个连续的内存块组成的。在中间插入元素时，如果当前内存块没有足够的空闲空间，deque 需要分配新的内存，并将部分元素移动到新内存中。此外，为了保持元素的连续性，deque 还需要将插入位置之后的元素向后移动，这可能涉及到跨越多个内存块的操作。
     
     需要注意的是，虽然中间插入的效率较低，但在某些情况下，如果插入操作不频繁或者数据量不大，这种开销可能可以接受。此外，如果知道要插入的元素范围（例如，插入一个子范围），可以一次性使用 deque 的 insert 函数的两个参数版本，这样可能会比逐个插入更高效。
     
     综上所述，deque 在中间进行插入操作的效率相对较低，主要原因是需要移动后续元素以腾出空间并保持连续性。在设计算法或选择数据结构时，应根据实际应用场景和操作需求来权衡 deque 的优点和缺点。如果频繁进行中间插入操作，并且对性能有较高要求，可能需要考虑其他数据结构，如列表（list）等。

2. 删除：

   - 尾部删除（pop_back）：效率高。与尾部插入类似，删除 deque 尾部的元素是一个快速操作，因为它只需简单地丢弃最后一个元素。

   - 头部删除（pop_front）：效率也相对较高。deque 的设计允许它在头部高效地删除元素，尽管这可能涉及到更新一些内部数据结构。

   - 中间删除（erase）：deque 在中间删除元素的效率不如其在头部和尾部的删除操作。当删除 deque 中间的元素时，需要移动后续元素以填充空缺，这可能导致 O(n) 的时间复杂度，其中 n 是被删除元素之后的元素数量。

     ```
     这是因为 deque 的内部实现是由多个连续的内存块组成的，每个内存块包含一定数量的元素。在删除中间元素后，为了保持元素的连续性，deque 需要将后续元素向前移动，这可能涉及到跨越多个内存块的操作。
     
     需要注意的是，虽然中间删除的效率较低，但在某些情况下，如果删除操作不频繁或者数据量不大，这种开销可能可以接受。此外，如果知道要删除的元素范围（例如，删除一个子范围），可以使用 deque 的 erase 函数的两个参数版本，一次性删除多个连续元素，这样可能会比逐个删除更高效。
     
     综上所述，deque 在中间进行删除操作的效率相对较低，主要原因是需要移动后续元素以保持连续性。在设计算法或选择数据结构时，应根据实际应用场景和操作需求来权衡 deque 的优点和缺点。如果频繁进行中间删除操作，并且对性能有较高要求，可能需要考虑其他数据结构，如列表（list）等。
     ```

3. 查找：

   - 随机查找：deque 支持随机访问，因此对于给定索引的查找，时间复杂度为 O(1)。但是，如果需要查找特定值，除非有额外的辅助数据结构（如哈希表），否则需要线性扫描，时间复杂度为 O(n)。

4. 修改（访问和修改元素）：

   - 随机访问和修改：由于 deque 支持随机访问，所以通过索引访问和修改元素的时间复杂度为 O(1)。然而，需要注意的是，如果索引跨越了 deque 内部的多个连续内存块，则可能会涉及额外的指针解引用操作，这可能会略微降低效率。

## 6. 补充

### 6.1 在中间插入代码

```c++
#include <deque>
#include <iostream>

int main() {
    std::deque<int> deq = {1, 2, 3, 4, 5}; // 初始化一个 deque

    int value_to_insert = 6; // 要插入的值
    int insert_position = 3; // 要插入的位置（从 0 开始计数）

    deq.insert(deq.begin() + insert_position, value_to_insert); // 在指定位置插入元素

    // 打印插入元素后的 deque
    for (const auto& element : deq) {
        std::cout << element << " ";
    }

    return 0;
}
```

### 6.2 在中间删除代码

```c++
#include <deque>
#include <iostream>

int main() {
    std::deque<int> deq = {1, 2, 3, 4, 5}; // 初始化一个 deque

    int delete_position = 2; // 要删除的位置（从 0 开始计数）

    deq.erase(deq.begin() + delete_position); // 在指定位置删除元素

    // 打印删除元素后的 deque
    for (const auto& element : deq) {
        std::cout << element << " ";
    }

    return 0;
}
```

### 6.3 查找中间的代码

```c++
#include <deque>
#include <iostream>

bool find_in_deque(const std::deque<int>& deq, int target) {
    for (const auto& element : deq) {
        if (element == target) {
            return true;
        }
    }
    return false;
}

int main() {
    std::deque<int> deq = {1, 2, 3, 4, 5}; // 初始化一个 deque

    int target_value = 3; // 要查找的值

    bool is_found = find_in_deque(deq, target_value); // 在 deque 中查找目标值

    if (is_found) {
        std::cout << "找到了目标值：" << target_value << std::endl;
    } else {
        std::cout << "未找到目标值：" << target_value << std::endl;
    }

    return 0;
}
```

### 6.4 修改中间的代码

```c++
#include <deque>
#include <iostream>

void modify_in_deque(std::deque<int>& deq, int target_value, int new_value) {
    for (auto it = deq.begin(); it != deq.end(); ++it) {
        if (*it == target_value) {
            *it = new_value; // 修改找到的元素
            return;
        }
    }
}

int main() {
    std::deque<int> deq = {1, 2, 3, 4, 5}; // 初始化一个 deque

    int target_value = 3; // 要修改的目标值
    int new_value = 6; // 新的值

    modify_in_deque(deq, target_value, new_value); // 在 deque 中查找并修改目标值

    // 打印修改元素后的 deque
    for (const auto& element : deq) {
        std::cout << element << " ";
    }

    return 0;
}
```