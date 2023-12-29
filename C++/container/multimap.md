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



## 4. 优点和缺点

## 5. 增删查改的效率

