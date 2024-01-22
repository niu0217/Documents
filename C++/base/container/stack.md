# stack

## 1. 问题

### 1.1 哪些可以选作stack的底层容器

在 C++ 中，以下容器可以作为 `std::stack` 的底层容器：

1. `std::deque`：默认的底层容器。`std::deque` 是一个双端队列，支持在头部和尾部高效地插入和删除元素，这与栈的操作特性相吻合。
2. `std::vector`：虽然不是默认选择，但也可以作为 `std::stack` 的底层容器。`std::vector` 是一个动态数组，支持随机访问，但在中间进行插入和删除操作时可能需要移动大量元素。
3. `std::list`：一个双向链表容器，支持在常数时间内在头部和尾部进行插入和删除操作，因此可以用作栈的底层容器。
4. 用户自定义的顺序容器（满足 SequenceContainer 要求）：如果你有一个符合 C++ 标准库中 SequenceContainer 要求的自定义容器，也可以用作 `std::stack` 的底层容器。

在选择底层容器时，应考虑以下因素：

- 性能需求：不同容器在插入、删除和访问元素方面的性能有所不同。例如，如果需要在栈中间进行插入和删除操作，`std::list` 可能是一个更好的选择。
- 内存使用：不同容器的内存使用和分配方式也不同。例如，`std::vector` 通常在内存中是连续存储的，而 `std::list` 和 `std::deque` 则不一定。
- 空间效率：某些容器可能需要额外的空间来存储元素之间的关系，如指针或偏移量。
- 随机访问需求：如果需要快速访问非栈顶元素，`std::vector` 或 `std::deque` 可能更适合，因为它们支持随机访问。

总的来说，选择哪个容器作为 `std::stack` 的底层容器取决于你的具体需求和应用场景。在大多数情况下，使用默认的 `std::deque` 就足够了，但如果对性能有特殊要求，可以考虑其他容器。

### 1.2 需要具备什么条件？

选择作为 `std::stack` 底层容器的容器需要具备以下条件：

1. 序列容器（SequenceContainer）：底层容器必须是一个序列容器，这意味着它应该支持在容器的末尾添加和删除元素。
2. 遵循 SequenceContainer 要求：底层容器应遵循 C++ 标准库中 SequenceContainer 的要求，包括但不限于以下几点：
   - 支持元素的插入和删除操作。
   - 提供常数时间的 `empty()` 函数，用于检查容器是否为空。
   - 提供常数时间的 `size()` 函数，返回容器中元素的数量。
3. 在容器末尾进行高效操作：由于栈是一种后进先出（LIFO）的数据结构，主要的操作是在栈顶（即容器的末尾）进行插入（push）和删除（pop）元素。因此，底层容器需要在容器末尾进行插入和删除操作时具有较高的效率。
4. 可选特性（取决于具体需求）：
   - 如果需要在栈中间进行插入和删除操作，那么底层容器应该支持这些操作，并且效率较高。在这种情况下，`std::list` 可能是一个更好的选择，因为它支持在常数时间内在头部和尾部进行插入和删除操作。
   - 如果需要快速访问非栈顶元素，那么底层容器应该支持随机访问。在这种情况下，`std::vector` 或 `std::deque` 可能更适合，因为它们支持随机访问。

总的来说，作为 `std::stack` 底层容器的候选容器应该是那些支持在容器末尾进行高效插入和删除操作的序列容器。具体的容器选择应根据实际应用的需求来确定。在 C++ 标准库中，`std::deque`、`std::vector` 和 `std::list` 都可以作为 `std::stack` 的底层容器。

## 2. 引入代码

```c++
#include <iostream>
#include <stack>

int main() {
    // 创建一个整数栈
    std::stack<int> myStack;

    // 入栈操作
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    // 查看栈顶元素，但不删除
    std::cout << "Top element is: " << myStack.top() << std::endl;

    // 出栈操作
    myStack.pop();

    // 检查栈是否为空
    if (myStack.empty()) {
        std::cout << "Stack is empty." << std::endl;
    } else {
        std::cout << "Stack is not empty." << std::endl;
    }

    // 获取栈的大小
    std::cout << "Size of the stack: " << myStack.size() << std::endl;

    return 0;
}
```

在这个示例中，我们使用了 C++ 标准库中的 `std::stack`，它已经包含了大部分常用函数：

- `push` 函数：将一个元素添加到栈顶。
- `top` 函数：查看栈顶元素但不删除。
- `pop` 函数：从栈顶删除一个元素。
- `empty` 函数：检查栈是否为空。
- `size` 函数：返回栈中的元素数量。

注意：C++ 标准库中的 `std::stack` 是基于容器适配器实现的，它需要一个底层容器来存储数据。默认情况下，它使用 `std::deque` 作为底层容器，但你也可以选择其他容器，如 `std::vector` 或 `std::list`。这个实现已经处理了异常情况，例如在出栈或查看栈顶元素时栈为空的情况。在生产环境中，你可以直接使用 `std::stack` 而无需关心内存管理和其他底层细节

## 3. 原理

### 3.1 简单分析

C++ 标准库中的 `std::stack` 是一个容器适配器，它提供了栈（Stack）数据结构的接口。栈是一种后进先出（LIFO, Last-In-First-Out）的数据结构，这意味着最后添加到栈中的元素将是第一个被移除的元素。

`std::stack` 的实现原理主要基于以下几点：

1. 底层容器：`std::stack` 并不直接管理内存和存储元素，而是依赖于一个底层容器（如 `std::deque`、`std::vector` 或 `std::list` 等）。默认情况下，`std::stack` 使用 `std::deque` 作为底层容器，但你可以通过模板参数指定其他容器。
2. 封装和接口简化：`std::stack` 提供了一个简洁的接口，包括 `push`, `pop`, `top`, 和 `empty` 等方法，这些方法都是对底层容器对应功能的封装。例如，`push` 方法实际上是在底层容器的末尾添加元素，而 `pop` 方法则是从底层容器的末尾删除元素。
3. 行为保证：尽管 `std::stack` 使用了特定的底层容器，但它确保了栈的行为特性，即后进先出。无论底层容器的具体实现细节如何，用户都可以依赖 `std::stack` 来实现栈的操作。

以下是一个简化的 `std::stack` 实现示例，展示了如何使用 `std::deque` 作为底层容器：

```c++
template <typename T, typename Container = std::deque<T>>
class Stack {
public:
    // 构造函数
    Stack() {}

    // 入栈操作
    void push(const T& value) {
        c.push_back(value);
    }

    // 出栈操作
    void pop() {
        if (!c.empty()) {
            c.pop_back();
        }
    }

    // 查看栈顶元素，但不删除
    T top() const {
        if (!c.empty()) {
            return c.back();
        }
        throw std::runtime_error("Stack is empty");
    }

    // 检查栈是否为空
    bool empty() const {
        return c.empty();
    }

private:
    Container c; // 底层容器
};
```

这个简化的实现展示了 `std::stack` 如何使用底层容器（在这个例子中是 `std::deque`）来提供栈的功能。实际的 C++ 标准库实现会更复杂，包括错误处理、异常安全性和其他优化。然而，基本的实现原理是相似的，即通过封装和适应底层容器的方法来提供栈的操作。

### 3.2 外部资料

https://blog.csdn.net/zhizhengguan/article/details/123898593

## 4. 优点和缺点

C++ 中 `std::stack` 的优点和缺点如下：

**优点：**

1. 简洁的接口：`std::stack` 提供了一个简单易用的接口，包括 `push`, `pop`, `top`, 和 `empty` 等方法，使得栈的操作变得直观和方便。
2. 容器适配器：`std::stack` 是一个容器适配器，它可以基于任何符合要求的序列容器（如 `std::deque`, `std::vector`, 或 `std::list`）实现，提供了灵活性。
3. 行为保证：`std::stack` 确保了栈的行为特性，即后进先出（LIFO），无论底层容器的具体实现细节如何。
4. 标准库支持：作为 C++ 标准库的一部分，`std::stack` 经过了广泛测试和优化，具有良好的跨平台兼容性和可靠性。
5. 异常安全性：`std::stack` 的操作通常设计为异常安全的，即使在发生异常时也能保持数据结构的完整性。

**缺点：**

1. 功能受限：`std::stack` 只提供了栈的基本操作，如果你需要栈之外的功能（如在中间插入或删除元素、直接访问非栈顶元素等），可能需要使用其他容器。
2. 性能依赖于底层容器：`std::stack` 的性能取决于所选择的底层容器。例如，如果使用 `std::vector` 作为底层容器，并且频繁在栈中间进行插入和删除操作，可能会导致元素的大量移动，影响性能。
3. 不可直接访问元素：`std::stack` 的设计不允许直接访问非栈顶元素，这在某些需要访问特定位置元素的场景下可能不太方便。
4. 默认容器选择可能不适用于所有情况：虽然 `std::deque` 是 `std::stack` 的默认底层容器，但并不一定适合所有应用场景。在某些情况下，可能需要选择其他容器以优化性能。

总的来说，`std::stack` 是一个非常实用的数据结构，适用于需要栈功能的大多数场景。然而，如果需要更复杂的数据结构或者对性能有特殊要求，可能需要考虑使用其他容器或自定义数据结构。

## 5. 底层容器的选择

### list

`std::list` 可以用作栈的底层容器。虽然 `std::list` 是一个双向链表容器，不像 `std::vector` 或 `std::deque` 那样支持随机访问，但它在头部（栈顶）进行插入和删除操作的效率很高，这符合栈的数据结构特性。

以下是一个使用 `std::list` 作为栈的底层容器的简单示例：

```c++
#include <iostream>
#include <list>

template <typename T>
class Stack {
public:
    void push(const T& value) {
        data.push_front(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_front();
        }
    }

    T top() const {
        if (!data.empty()) {
            return data.front();
        }
        throw std::runtime_error("Stack is empty");
    }

    bool empty() const {
        return data.empty();
    }

private:
    std::list<T> data;
};
```

在这个示例中，我们创建了一个自定义的栈类，该类使用 `std::list` 作为其内部数据结构来模拟栈的行为。`push`、`pop` 和 `top` 方法分别对应于在栈顶插入元素、删除栈顶元素和获取栈顶元素的操作。由于 `std::list` 支持在常数时间内在头部进行插入和删除操作，因此它作为栈的底层容器是可行的。然而，需要注意的是，如果需要频繁访问非栈顶元素或者在中间进行插入和删除操作，`std::list` 可能不是最佳选择。

### forward_list

`std::forward_list` 可以用作栈的底层容器，但是需要注意以下几点：

1. `std::forward_list` 是一个单向链表容器，它不支持在 O(1) 时间复杂度内随机访问元素。因此，如果你需要快速访问非栈顶元素或者在中间进行插入和删除操作，`std::forward_list` 可能不是一个理想的选择。
2. 由于 `std::forward_list` 的数据结构特性，使用它作为栈的底层容器可能会增加额外的空间开销，因为每个元素都需要存储指向下一个元素的指针。

如果你想使用 `std::forward_list` 作为栈的底层容器，你可以自定义一个栈类来封装 `std::forward_list` 的相关操作。以下是一个简单的示例：

```c++
#include <forward_list>

template <typename T>
class Stack {
public:
    void push(const T& value) {
        data.push_front(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_front();
        }
    }

    T top() const {
        if (!data.empty()) {
            return data.front();
        }
        throw std::runtime_error("Stack is empty");
    }

    bool empty() const {
        return data.empty();
    }

private:
    std::forward_list<T> data;
};
```

这个实现展示了如何使用 `std::forward_list` 作为栈的底层容器。然而，如前所述，这可能不是最高效的实现，特别是在频繁进行入栈和出栈操作的情况下。在实际应用中，你可能需要根据具体需求和性能考虑选择更适合的容器作为栈的底层实现。