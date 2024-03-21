# 优先级队列

## 基础知识

在C++中，`std::priority_queue` 是由 STL 提供的标准库模板类，它提供了一个优先级队列的实现。`std::priority_queue` 具有以下常用的模板参数：

1. **T (Mandatory)**: 储存在队列中的元素类型。
2. **Container (Optional)**: 用来储存元素的底层容器类型。默认情况下，默认为 `std::vector<T>`，但可以自定义为其他容器，比如 `std::deque<T>` 或者 `std::list<T>`。
3. **Compare (Optional)**: 用于定义元素优先级顺序的比较函数类型。默认情况下，采用 `std::less<T>`，即元素以降序排列。如果需要自定义优先级顺序，则可以通过提供自定义的比较函数来实现。

下面是 `std::priority_queue` 的一般模板声明：

```cpp
template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class priority_queue;
```

这里，`T` 是元素类型，`Container` 是底层容器类型，`Compare` 是比较函数类型。

在使用时，可以根据实际需要指定模板参数。例如，如果想要使用 `std::deque` 作为底层容器，可以这样指定：

```cpp
std::priority_queue<int, std::deque<int>> myPriorityQueue;
```

如果需要自定义比较函数，可以这样指定：

```cpp
auto cmp = [](int a, int b) { return a > b; };  // 自定义升序排列的比较函数
std::priority_queue<int, std::vector<int>, decltype(cmp)> myPriorityQueue(cmp);
```

通过了解这些参数，可以根据具体情况来选择合适的配置。

另一个例子：

```c++
#include <iostream>
#include <queue>

int main() {
    // 创建一个最大优先级队列
    std::priority_queue<int> maxPriorityQueue;

    // 插入元素
    maxPriorityQueue.push(30);
    maxPriorityQueue.push(100);
    maxPriorityQueue.push(25);
    maxPriorityQueue.push(40);

    // 访问队首元素
    std::cout << "队首元素：" << maxPriorityQueue.top() << std::endl;

    // 弹出队首元素
    maxPriorityQueue.pop();

    // 遍历队列中的元素
    std::cout << "遍历队列中的元素：" << std::endl;
    while (!maxPriorityQueue.empty()) {
        std::cout << maxPriorityQueue.top() << " ";
        maxPriorityQueue.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

## 题目

