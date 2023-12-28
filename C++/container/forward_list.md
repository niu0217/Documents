# forward_list

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <forward_list>

int main() {
    // 创建一个空的forward_list
    std::forward_list<int> flist;

    // 在forward_list末尾添加元素
    flist.push_front(10);
    flist.push_front(20);
    flist.push_front(30);

    // 在forward_list开头添加元素
    flist.push_front(0);

    // 访问元素
    auto it = flist.begin();
    std::cout << "First element: " << *it << std::endl;
    ++it;
    std::cout << "Second element: " << *it << std::endl;

    // 修改元素
    it = flist.begin();
    *it = 5;
    std::cout << "After modification, first element: " << *it << std::endl;

    // 获取forward_list的大小
    std::size_t listSize = 0;
    for(const auto& element: flist) {
        listSize++;
    }
    std::cout << "Size of the forward_list: " << listSize << std::endl;

    // 检查forward_list是否为空
    if (flist.empty()) {
        std::cout << "Forward_list is empty." << std::endl;
    } else {
        std::cout << "Forward_list is not empty." << std::endl;
    }

    // 使用范围for循环遍历forward_list
    for (const auto& element : flist) {
        std::cout << "Element: " << element << std::endl;
    }

    // 使用before_begin()和end()进行迭代
    auto beforeBegin = flist.before_begin();
    for (auto it = flist.begin(); it != flist.end(); ++it) {
        std::cout << "Element: " << *it << std::endl;
        beforeBegin = it;
    }

    // 删除满足条件的元素（需要自定义函数，因为std::remove_if不适用于forward_list）
    auto removeEven = [](int i) { return i % 2 == 0; };
    for (auto it = flist.begin(); it != flist.end(); ) {
        if (removeEven(*it)) {
            it = flist.erase_after(beforeBegin);
        } else {
            ++it;
            beforeBegin = it;
        }
    }

    // 清空forward_list
    flist.clear();

    return 0;
}
```

1. **flist.before_begin()**

`flist.before_begin()` 是 `std::forward_list` 提供的一个成员函数，它返回一个特殊的迭代器，该迭代器指向列表中第一个元素之前的位置。

在双向链表（如 `std::list`）中，每个元素都有两个指针，一个指向前一个元素，另一个指向后一个元素。而在单向链表（如 `std::forward_list`）中，每个元素只有一个指针，指向下一个元素。因此，单向链表不支持反向迭代。

为了能够在单向链表的开头插入元素，`std::forward_list` 提供了 `before_begin()` 函数，返回一个 "before begin" 迭代器。这个迭代器并不是指向任何实际元素，而是位于列表的第一个元素之前。

当你需要在单向链表的开头插入元素时，可以使用 `before_begin()` 返回的迭代器与 `insert_after()` 函数结合：

```c++
flist.insert_after(flist.before_begin(), newValue);
```

这将在单向链表的开头插入一个新元素 `newValue`。注意，`before_begin()` 返回的迭代器不能用于解引用或删除操作，因为它并不指向任何实际元素。它的主要用途是在单向链表的开头进行插入操作。

2. **flist.erase_after()**

`flist.erase_after(iterator)` 是 `std::forward_list` 提供的一个成员函数，用于删除指定迭代器之后的元素。

这个函数接受一个参数，该参数是一个迭代器，指向需要删除的元素的前一个元素。因为 `std::forward_list` 是单向链表，所以不能直接通过迭代器删除元素，而需要通过其前一个元素来定位要删除的元素。

以下是一个使用 `erase_after()` 函数的例子：

```c++
std::forward_list<int> flist = {1, 2, 3, 4, 5};

// 删除第二个元素（值为2）
auto it = flist.begin();
++it; // 移动迭代器到第二个元素之前的位置
flist.erase_after(it);

// 现在，flist包含：1, 3, 4, 5
```

在这个例子中，我们首先创建了一个包含五个整数的 `std::forward_list`。然后，我们获取了一个指向第二个元素之前的迭代器 `it`。接下来，我们调用 `erase_after(it)` 函数，这将删除 `it` 指向的元素之后的元素，即值为2的元素。最后，列表 `flist` 将包含剩余的元素：1, 3, 4, 5。