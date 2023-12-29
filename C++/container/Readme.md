# C++中的容器

## 1. 概述

C++中的容器是标准库提供的一系列数据结构，用于存储和管理不同类型的元素。以下是一些主要的C++容器：

1. **顺序容器**：
   - `std::vector`：动态数组，支持随机访问，插入和删除元素可能导致大量元素移动。
   - `std::array`：固定大小的数组，大小在编译时确定，不支持动态增长。
   - `std::list`：双向链表，插入和删除元素效率高，但不支持随机访问。
   - `std::forward_list`：单向链表，更节省空间，但只能向前遍历。
   - `std::deque`：双端队列，两端都可以高效地插入和删除元素。
2. **关联容器**：
   - `std::set`：有序集合，不允许重复元素，插入、查找和删除操作的时间复杂度为O(log n)。
   - `std::multiset`：有序集合，允许重复元素。
   - `std::map`：键值对映射，键是唯一的，按键排序，插入、查找和删除操作的时间复杂度为O(log n)。
   - `std::multimap`：键值对映射，键可以重复，按键排序。
   - `std::unordered_set`：哈希集合，不允许重复元素，插入、查找和删除操作的平均时间复杂度为O(1)。
   - `std::unordered_multiset`：哈希集合，允许重复元素。
   - `std::unordered_map`：哈希映射，键是唯一的，插入、查找和删除操作的平均时间复杂度为O(1)。
   - `std::unordered_multimap`：哈希映射，键可以重复。
3. **容器适配器**：
   - `std::stack`：后进先出（LIFO）的容器，基于其他顺序容器实现。
   - `std::queue`：先进先出（FIFO）的容器，基于其他顺序容器实现。
   - `std::priority_queue`：优先队列，元素按照其优先级进行排序。

这些容器提供了多种操作，如插入、删除、查找、遍历等，并且可以通过迭代器进行元素访问。选择合适的容器取决于你的具体需求，包括数据的访问模式、元素数量、内存使用、性能要求等因素。在现代C++编程中，还推荐使用智能指针（如`std::unique_ptr`、`std::shared_ptr`）来管理容器中的对象生命周期，以提高代码的安全性和可维护性。

## 2. 容器

### 2.1 顺序容器

[array.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/array.md)

[vector.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/vector.md)

[list.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/list.md)

[forward_list.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/forward_list.md)

[deque.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/deque.md)

### 2.2 关联容器

[set.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/set.md)

[multiset.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/multiset.md)

[map.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/map.md)

[multimap.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/multimap.md)

[unordered_set.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/unordered_set.md)

[unordered_multiset.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/unordered_multiset.md)

### 2.3 容器适配器

[stack.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/stack.md)

[queue.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/queue.md)

[priority_queue.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/container/priority_queue.md)
