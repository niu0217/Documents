# queue

## 1. 问题

### 1.1 哪些容器可以用作queue的底层容器

以下容器可以作为 `std::queue` 的底层容器：

1. `std::deque`：默认的底层容器。`std::deque` 是一个双端队列，支持在头部和尾部高效地插入和删除元素，这与队列的操作特性相吻合。
2. `std::vector`：虽然不是默认选择，但也可以作为 `std::queue` 的底层容器。`std::vector` 是一个动态数组，支持随机访问，但在中间进行插入和删除操作时可能需要移动大量元素。
3. `std::list`：一个双向链表容器，支持在常数时间内在头部和尾部进行插入和删除操作，因此可以用作队列的底层容器。

不可以作为 `std::queue` 底层容器的容器主要包括那些不支持在头部和尾部高效插入和删除元素的数据结构，如 `std::set`、`std::map` 等关联容器。这些容器的设计目标和操作特性与队列的需求不符。

优缺点如下：

- `std::deque`：
  - 优点：在头部和尾部插入和删除元素的效率高，与队列的操作特性匹配。(也支持随机访问)
  - 缺点：在中间插入和删除元素可能需要移动大量元素，如果频繁在中间进行操作，性能可能会受到影响。
- `std::vector`：
  - 优点：支持随机访问，如果需要快速访问队列中的特定元素，这是一个优势。
  - 缺点：在中间插入和删除元素可能需要移动大量元素，如果频繁在中间进行操作，性能可能会受到影响。此外，由于其内存分配策略，连续的入队和出队操作可能导致内存碎片。
- `std::list`：
  - 优点：在头部和尾部插入和删除元素的效率高，且不需要移动其他元素，适合频繁在头部和尾部进行操作的场景。
  - 缺点：不支持随机访问，如果需要快速访问队列中的特定元素，性能较低。此外，每个元素都需要额外的空间存储指针，空间效率相对较低。

总的来说，选择哪个容器作为 `std::queue` 的底层容器取决于你的具体需求和应用场景。在大多数情况下，使用默认的 `std::deque` 就足够了，但如果对性能有特殊要求，可以考虑其他容器。在选择时应权衡插入/删除效率、内存使用和随机访问需求等因素。

## 2. 引入代码

```c++
#include <iostream>
#include <queue>

int main() {
    // 创建一个整数队列
    std::queue<int> myQueue;

    // 入队操作
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    // 查看队头元素，但不删除
    std::cout << "Front element is: " << myQueue.front() << std::endl;

    // 查看队尾元素，但不删除
    std::cout << "Back element is: " << myQueue.back() << std::endl;

    // 出队操作
    myQueue.pop();

    // 检查队列是否为空
    if (myQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    // 获取队列的大小
    std::cout << "Size of the queue: " << myQueue.size() << std::endl;

    return 0;
}
```

在这个示例中，我们使用了 C++ 标准库中的 `std::queue`，它已经包含了大部分常用函数：

- `push` 函数：将一个元素添加到队尾。
- `front` 函数：查看队头元素但不删除。
- `back` 函数：查看队尾元素但不删除。
- `pop` 函数：从队头删除一个元素。
- `empty` 函数：检查队列是否为空。
- `size` 函数：返回队列中的元素数量。

注意：C++ 标准库中的 `std::queue` 是基于容器适配器实现的，它需要一个底层容器来存储数据。默认情况下，它使用 `std::deque` 作为底层容器，但你也可以选择其他容器，如 `std::vector` 或 `std::list`。这个实现已经处理了异常情况，例如在出队或查看队头元素时队列为空的情况。在生产环境中，你可以直接使用 `std::queue` 而无需关心内存管理和其他底层细节。

## 3. 原理

### 3.1 简单分析

C++ 标准库中的 `std::queue` 是一个容器适配器，它提供了队列（Queue）数据结构的接口。队列是一种先进先出（FIFO, First-In-First-Out）的数据结构，这意味着最先添加到队列中的元素将是第一个被移除的元素。

`std::queue` 的实现原理主要基于以下几点：

1. 底层容器：`std::queue` 并不直接管理内存和存储元素，而是依赖于一个底层容器（如 `std::deque`、`std::vector` 或 `std::list` 等）。默认情况下，`std::queue` 使用 `std::deque` 作为底层容器，但你可以通过模板参数指定其他容器。
2. 封装和接口简化：`std::queue` 提供了一个简洁的接口，包括 `push`, `pop`, `front`, 和 `empty` 等方法，这些方法都是对底层容器对应功能的封装。例如，`push` 方法实际上是在底层容器的末尾添加元素，而 `pop` 方法则是从底层容器的开头删除元素。
3. 行为保证：尽管 `std::queue` 使用了特定的底层容器，但它确保了队列的行为特性，即先进先出。无论底层容器的具体实现细节如何，用户都可以依赖 `std::queue` 来实现队列的操作。

以下是一个简化的 `std::queue` 实现示例，展示了如何使用 `std::deque` 作为底层容器：

```c++
template <typename T, typename Container = std::deque<T>>
class Queue {
public:
    // 构造函数
    Queue() {}

    // 入队操作
    void push(const T& value) {
        c.push_back(value);
    }

    // 出队操作
    void pop() {
        if (!c.empty()) {
            c.pop_front();
        }
    }

    // 查看队头元素，但不删除
    T front() const {
        if (!c.empty()) {
            return c.front();
        }
        throw std::runtime_error("Queue is empty");
    }

    // 检查队列是否为空
    bool empty() const {
        return c.empty();
    }

private:
    Container c; // 底层容器
};
```

### 3.2 外部资料

https://zhuanlan.zhihu.com/p/542115773

queue（普通队列）是一个专为 FIFO 设计的容器适配器，也即只能从一端插入、从另一端删除；所谓容器适配器，是指它本身只是一个封装层，必须依赖指定的底层容器（通过模板参数中的`class Container`指定）才能实现具体功能。

容器适配器实际上是C++设计模式的一种 —— 称为 Adapter 模式（适配器模式），Adapter 模式的目的是将第三方库提供的接口做一个封装和转化，使其适配自己工程中预留的接口，或者适应自己工程的调用风格。换句话说，Adapter 模式的目的是将被调用类（如第三方库）的接口转化为希望的接口。

回到正题，queue 可以接纳任何一个至少支持下列接口的容器作为底层容器：

> ```
> empty(); size(); front(); back(); push_back(); pop_front().
> ```

在标准模板库容器中，deque 和 list 满足上述要求，当然用户也可以自定义一个满足上述要求的容器。通过模板参数可以看出，默认情况下，queue 使用 deque 作为底层容器。

## 4. 底层容器举例

### 4.1 list

```c++
#include <iostream>
#include <list>

template <typename T>
class Queue {
public:
    // 构造函数
    Queue() {}

    // 入队操作
    void push(const T& value) {
        list.push_back(value);
    }

    // 出队操作
    void pop() {
        if (!list.empty()) {
            list.pop_front();
        }
    }

    // 查看队头元素（但不删除）
    T front() const {
        if (!list.empty()) {
            return list.front();
        }
        throw std::runtime_error("Queue is empty");
    }

    // 检查队列是否为空
    bool empty() const {
        return list.empty();
    }

private:
    std::list<T> list; // 使用 std::list 作为底层容器
};

int main() {
    // 创建一个使用自定义 Queue 类（基于 std::list）的对象
    Queue<int> myQueue;

    // 入队操作
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    // 出队操作
    myQueue.pop();

    // 查看队头元素（但不删除）
    std::cout << "Front element is: " << myQueue.front() << std::endl;

    // 检查队列是否为空
    if (myQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    return 0;
}
```



