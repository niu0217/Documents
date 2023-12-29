# multimap

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <map>

int main() {
    // 初始化一个multimap，键为int类型，值为string类型
    std::multimap<int, std::string> myMultimap;

    // 增：插入元素
    myMultimap.insert(std::make_pair(1, "Apple"));
    myMultimap.insert(std::make_pair(2, "Banana"));
    myMultimap.insert(std::make_pair(1, "Cherry")); // 同一键可有多个值
    myMultimap.insert(std::make_pair(1, "niu0217")); // 同一键可有多个值
    myMultimap.insert(std::make_pair(1, "Tom")); // 同一键可有多个值

    // 查：通过键查找所有值
    auto range = myMultimap.equal_range(1);
    for (auto it = range.first; it != range.second; it++) {
        const auto& entry = *it;
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    }

    // 改：multimap本身不支持直接修改已存在的元素，
    // 但可以通过删除旧元素并插入新元素实现“修改”

    // 先删除特定键的一个实例（这里删除第一个"1"对应的值）
    range = myMultimap.equal_range(1);
    if (range.first != range.second) {
        myMultimap.erase(range.first); // 删除第一个键为1的元素
        myMultimap.insert(std::make_pair(1, "Date")); // 插入新的键值对
    }

    // 查找修改后的所有值
    range = myMultimap.equal_range(1);
    for (auto it = range.first; it != range.second; it++) {
        const auto& entry = *it;
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    }

    // 删：删除与某个键相关的所有键值对
    myMultimap.erase(1);

    // 遍历multimap
    for (const auto& entry : myMultimap) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    }

    // 清空multimap
    myMultimap.clear();

    return 0;
}
```

在这个示例中：

- `insert` 函数用于插入键值对。
- 使用 `equal_range` 获取给定键的所有关联值。
- 要“修改”一个键的值，首先需要找到该键并通过 `erase` 删除对应的键值对，然后插入新的键值对。
- `erase(key)` 可以删除与指定键相关联的所有键值对。
- 最后，遍历整个multimap并清空它。

## 3. 原理

C++中的`std::multimap`也是基于关联容器的一种实现，类似于`std::map`，但允许键值对的键可以重复。在C++标准库中，`std::multimap`底层通常采用红黑树（Red-Black Tree）作为数据结构来维护键值对的存储和排序。

具体实现原理如下：

1. **数据结构**：
   - 每个节点代表一个键值对，并且包含了指向左右子节点的指针。
   - 红黑树是一种自平衡二叉查找树，每个节点除了包含键、值以及左右子节点指针外，还具有颜色属性（红色或黑色），用于保证插入、删除操作后，树的高度始终保持在O(log n)级别，从而提供稳定的查找性能。
2. **插入操作**：
   - 插入新元素时，根据键的大小关系找到合适的位置。与`std::map`不同的是，当遇到相同的键时，新节点会被添加到相同键值对的集合中，即键相同的节点会在同一分支下按照插入顺序排列。
3. **查找操作**：
   - 查找特定键时，利用二叉搜索树特性进行查找。如果只想查找第一个匹配的键，使用`find()`；如果需要查找所有匹配的键及其对应的值，可以使用`equal_range()`函数，它会返回一个迭代器范围，表示所有键等于给定键的元素范围。
4. **删除操作**：
   - 删除一个键值对时，首先定位到要删除的节点。由于可能有多个键相同的节点，所以需要指定是删除键值对的一个实例还是全部实例。
5. **有序性**：
   - `std::multimap`保持了键的有序性，即使键相同，也按照插入顺序排列。

总结来说，`std::multimap`通过红黑树的数据结构实现了键值对的有序存储和快速查找，同时允许键的重复出现，并支持按顺序遍历相同键的所有值。

## 4. 优点和缺点

C++中`std::multimap`的优点：

1. **有序性**：`std::multimap`中的元素根据键值自动排序，插入时会按照升序排列。这使得可以根据键的大小进行高效查找、遍历和区间查询。
2. **键重复允许**：与`std::map`不同，`std::multimap`允许键值对的键重复出现，并且每个键可以对应多个值，这些值按插入顺序排列。
3. **高效查找**：由于底层通常使用红黑树实现，因此查找操作的时间复杂度为O(log n)，其中n是容器中的元素数量。
4. **范围查询**：提供了`equal_range()`函数，可以返回一个迭代器范围，包含所有具有特定键的所有元素，方便处理重复键的情况。
5. **动态调整**：在插入或删除元素后，能够自动维护平衡状态，保持高效的查找性能。

缺点：

1. **空间开销**：每个节点需要存储键、值、左右子节点指针以及颜色信息，相较于不考虑顺序的数据结构（如哈希表），空间效率较低。
2. **插入和删除成本较高**：插入和删除操作的时间复杂度均为O(log n)。当需要频繁插入和删除大量数据时，可能不如基于哈希表的`unordered_multimap`快。
3. **无随机访问**：无法像数组那样通过索引直接访问特定位置的元素。
4. **初始化和复制成本**：创建一个新的`multimap`或者复制一个现有的`multimap`时，需要遍历所有元素，因此时间复杂度为O(n)。
5. **对键的修改受限**：一旦元素插入到`multimap`中，改变键值会导致元素移动，需要先删除再插入新的键值对。而且因为键关联了值的位置，所以不能单独更改键而不影响整体顺序。
6. **非线性时间的特定操作**：某些操作，如查找特定排名的元素或获取特定键下所有值的数量，需要O(n)的时间。

## 5. 增删查改的效率

C++中`std::multimap`的增删查改效率基于其底层数据结构，通常情况下是红黑树（Red-Black Tree）实现：

1. **插入（Insertion）**：
   - 插入一个元素的时间复杂度为O(log n)，其中n是当前容器中的元素数量。在插入过程中，新节点会被放置到适当的位置以保持键值对的有序性，并且可能需要进行红黑树的旋转和颜色调整操作以维持树的平衡。
2. **查找（Search）**：
   - 查找一个特定键或键范围内的所有元素的时间复杂度也是O(log n)。由于红黑树是一种自平衡二叉搜索树，可以使用二分查找法快速定位键对应的值或区间。
3. **修改（Modification）**：
   - 修改一个已存在键对应的值并不直接支持，因为`std::multimap`的设计理念是以键关联多个值。如果要更改某个值，你需要先找到该键下的相应元素并删除它，然后插入新的键值对。
   - 但是，如果你仅想改变某一个键下对应的一个具体值，你必须先通过迭代器找到这个元素，然后再替换其值，这个过程本身时间复杂度接近于常数时间，但首先找到该元素仍需O(log n)的时间。
4. **删除（Deletion）**：
   - 删除一个键值对的时间复杂度同样为O(log n)，涉及到查找、从红黑树中移除节点以及可能的结构调整来保持树的平衡。

综上所述，`std::multimap`提供了稳定的对数时间复杂度的增删查改操作，尤其适用于需要根据键排序且允许键重复出现的情况。不过与基于哈希表实现的`unordered_multimap`相比，在大规模数据集上的平均性能可能会略低，因为哈希表在理想情况下提供常数时间的查找和插入删除操作（假设没有严重的哈希冲突）。