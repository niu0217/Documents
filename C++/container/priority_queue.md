# priority_queue

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <queue>
#include <vector>

struct Compare {
    bool operator()(const int& a, const int& b) const {
        return a > b; // 优先级队列默认是小顶堆，这里改为大顶堆
    }
};

int main() {
    // 创建一个整数优先级队列，使用自定义比较函数
    std::priority_queue<int, std::vector<int>, Compare> myPriorityQueue;

    // 入队操作
    myPriorityQueue.push(3);
    myPriorityQueue.push(1);
    myPriorityQueue.push(5);

    // 查看队头元素（即最高优先级元素），但不删除
    std::cout << "Top priority element is: " << myPriorityQueue.top() << std::endl;

    // 出队操作（删除并返回最高优先级元素）
    int topElement = myPriorityQueue.top();
    myPriorityQueue.pop();

    std::cout << "After popping the top element, the new top priority element is: " << myPriorityQueue.top() << std::endl;

    // 检查优先级队列是否为空
    if (myPriorityQueue.empty()) {
        std::cout << "Priority queue is empty." << std::endl;
    } else {
        std::cout << "Priority queue is not empty." << std::endl;
    }

    // 获取优先级队列的大小
    std::cout << "Size of the priority queue: " << myPriorityQueue.size() << std::endl;

    return 0;
}
```

**代码解析：**

`std::priority_queue<int, std::vector<int>, Compare> myPriorityQueue;` 是一个 `std::priority_queue` 的实例化声明，它具有以下组成部分：

1. `int`：优先级队列中元素的类型。在这个例子中，队列中的元素是整数。
2. `std::vector<int>`：底层容器的类型。优先级队列使用这个容器来存储元素。在这个例子中，底层容器是 `std::vector<int>`。
3. `Compare`：比较函数对象的类型。这个对象用于确定队列中元素的优先级顺序。在这个例子中，我们定义了一个名为 `Compare` 的结构体，其中包含一个重载的 `operator()`，该运算符接受两个 `int` 类型的参数，并返回一个布尔值。如果 `a` 应该在 `b` 之前（即 `a` 的优先级高于 `b`），则返回 `true`；否则返回 `false`。
4. `myPriorityQueue`：优先级队列对象的名称。

这个声明创建了一个名为 `myPriorityQueue` 的优先级队列，其中元素类型为 `int`，底层容器为 `std::vector<int>`，并且使用自定义的比较函数对象 `Compare` 来确定元素的优先级顺序。在实际使用中，你可以根据需要替换这些参数，以适应你的特定需求。

**总结：**

在这个示例中，我们使用了 C++ 标准库中的 `std::priority_queue`，它已经包含了大部分常用函数：

- `push` 函数：将一个元素添加到优先级队列中。
- `top` 函数：查看队头元素（即最高优先级元素），但不删除。
- `pop` 函数：删除并返回队头元素（即最高优先级元素）。
- `empty` 函数：检查优先级队列是否为空。
- `size` 函数：返回优先级队列中的元素数量。

注意：在本示例中，我们使用了一个自定义的比较函数 `Compare` 来实现大顶堆。默认情况下，`std::priority_queue` 实现的是小顶堆。你可以根据实际需求选择合适的比较函数。

此外，`std::priority_queue` 是基于容器适配器实现的，它需要一个底层容器来存储数据。默认情况下，它使用 `std::vector` 作为底层容器，但你也可以选择其他容器，如 `std::deque`。这个实现已经处理了异常情况，例如在出队或查看队头元素时队列为空的情况。在生产环境中，你可以直接使用 `std::priority_queue` 而无需关心内存管理和其他底层细节。

## 3. 原理

C++ 中的 `std::priority_queue` 是一个容器适配器，它基于堆数据结构实现。具体来说，`std::priority_queue` 默认使用最大堆（也可以通过自定义比较函数改为最小堆）来维护元素的顺序。

以下是一个简化的 `std::priority_queue` 实现原理概述：

1. 堆数据结构：堆是一种特殊的树形数据结构，其中每个节点的值都大于或等于（对于最大堆）其子节点的值。这保证了堆顶元素（根节点）始终具有最高优先级。
2. 底层容器：`std::priority_queue` 使用一个底层容器（如 `std::vector` 或 `std::deque`）来存储元素。这些元素在内存中按照堆的规则进行组织。
3. 插入元素：当向优先级队列中插入一个新元素时，会将其添加到底层容器的末尾，并通过上浮操作（sift up）确保堆的性质得到保持。上浮操作涉及到将新插入的元素与其父节点进行比较，如果新元素的优先级更高，则与父节点交换位置，然后继续与新的父节点比较，直到找到合适的位置或者到达根节点。
4. 删除元素（出队操作）：删除 `std::priority_queue` 中的元素（即获取并删除最高优先级元素）涉及到取出堆顶元素（根节点），然后将最后一个元素移动到堆顶，并通过下沉操作（sift down）确保堆的性质得到保持。下沉操作涉及到将新的堆顶元素与其子节点进行比较，如果子节点中的某个元素的优先级更高，则与该子节点交换位置，然后继续与新的子节点比较，直到找到合适的位置或者到达叶子节点。
5. 访问元素：`std::priority_queue` 只提供了对堆顶元素（最高优先级元素）的访问，可以通过 `top()` 函数获取堆顶元素，但不能直接访问其他元素。
6. 比较函数：`std::priority_queue` 可以接受一个可选的比较函数对象作为第三个模板参数，这个函数对象用于确定元素的优先级顺序。默认情况下，`std::priority_queue` 使用小于运算符 `<` 来比较元素，这样就实现了最大堆。

总的来说，`std::priority_queue` 的实现原理是利用堆数据结构和底层容器来高效地维护元素的优先级顺序，并提供插入、删除和访问堆顶元素的操作。由于堆操作的时间复杂度为 O(log n)，因此 `std::priority_queue` 的主要操作（插入和删除）具有较好的性能。

## 4. 优点和缺点

`std::priority_queue` 在 C++ 中具有以下优点和缺点：

优点：

1. 高效性：由于 `std::priority_queue` 基于堆数据结构实现，插入、删除（出队）和访问最高优先级元素的时间复杂度均为 O(log n)，其中 n 是队列中的元素数量。这使得 `std::priority_queue` 在处理大量数据时具有较高的效率。
2. 优先级管理：`std::priority_queue` 自动维护元素的优先级顺序，无需在代码中手动排序或管理优先级。
3. 底层容器可配置：可以指定不同的底层容器（如 `std::vector` 或 `std::deque`），以适应不同的内存使用和性能需求。
4. 灵活性：通过提供自定义比较函数对象，可以轻松地改变元素的优先级排序规则。
5. 标准库支持：作为 C++ 标准库的一部分，`std::priority_queue` 具有良好的跨平台兼容性和广泛的社区支持。

缺点：

1. 只能访问最高优先级元素：`std::priority_queue` 只提供了对最高优先级元素的访问，无法直接访问或遍历队列中的其他元素。
2. 插入和删除操作可能影响性能：虽然插入和删除操作的时间复杂度为 O(log n)，但在某些特定情况下（例如频繁的插入和删除操作），这些操作可能会导致频繁的内存分配和释放，影响性能。
3. 不保证元素的顺序：除了最高优先级元素外，`std::priority_queue` 不保证元素的相对顺序。如果需要保持元素的原始顺序或者有其他特定顺序要求，可能需要使用其他数据结构。
4. 默认为最大堆：如果不提供自定义比较函数，`std::priority_queue` 默认实现的是最大堆，这意味着默认情况下优先级最高的元素会被首先处理。如果需要最小堆的行为，需要提供一个反转比较结果的自定义比较函数。
5. 无直接修改元素优先级的操作：`std::priority_queue` 不提供直接修改元素优先级的接口。如果需要改变一个已存在于队列中的元素的优先级，需要先删除该元素，然后重新插入。

总的来说，`std::priority_queue` 是一个适用于需要高效管理和处理优先级任务的数据结构，但需要注意其限制并根据具体应用场景选择合适的数据结构。

## 5. 增删查改的效率

`std::priority_queue` 的增删查改效率如下：

1. 插入（增）：插入元素到 `std::priority_queue` 中的时间复杂度为 O(log n)，其中 n 是队列中的元素数量。这是因为插入元素后需要通过上浮操作（sift up）来维护堆的性质。
2. 删除（删）：删除 `std::priority_queue` 中的元素（即获取并删除最高优先级元素，也称为出队操作）的时间复杂度也为 O(log n)。这是因为删除堆顶元素后需要将最后一个元素移动到堆顶，并通过下沉操作（sift down）来维护堆的性质。
3. 查询（查）：
   - 访问最高优先级元素：通过 `top()` 函数访问最高优先级元素的时间复杂度为 O(1)，因为堆顶元素总是可以直接访问。
   - 访问其他元素：`std::priority_queue` 不支持直接访问或遍历队列中的其他元素，因此查询其他元素的时间复杂度无法确定。
4. 修改（改）：`std::priority_queue` 不提供直接修改元素优先级的接口。如果需要改变一个已存在于队列中的元素的优先级，通常需要先删除该元素（时间复杂度为 O(log n)），然后再重新插入（时间复杂度为 O(log n)），所以总的时间复杂度为 O(log n)。

综上所述，`std::priority_queue` 在插入、删除和修改元素时具有较高的效率，时间复杂度均为 O(log n)。然而，它只支持高效地访问最高优先级元素，不支持直接访问或遍历队列中的其他元素。在实际应用中，应根据具体需求选择合适的数据结构。如果需要频繁访问队列中的所有元素或者有其他特定顺序要求，可能需要考虑使用其他数据结构，如 `std::vector` 或 `std::list`。

## 6. 实际应用代码

```c++
#include <iostream>
#include <queue>
#include <vector>
#include <string>

// 定义任务类，包含任务名称和优先级
struct Task {
    std::string name;
    int priority;

    // 构造函数
    Task(const std::string& n, int p) : name(n), priority(p) {}

    // 重载小于运算符，用于比较两个任务的优先级
    bool operator<(const Task& other) const {
        return priority > other.priority; // 实现大顶堆（优先级越高，优先级越低）
    }
};

int main() {
    // 创建一个优先级队列，用于存储任务
    std::priority_queue<Task> taskQueue;

    // 添加一些任务到优先级队列
    taskQueue.push(Task("Task1", 3));
    taskQueue.push(Task("Task2", 1));
    taskQueue.push(Task("Task3", 2));
    taskQueue.push(Task("Task4", 5));
    taskQueue.push(Task("Task5", 4));

    // 处理优先级最高的任务，直到队列为空
    while (!taskQueue.empty()) {
        // 获取并删除优先级最高的任务
        Task currentTask = taskQueue.top();
        taskQueue.pop();

        // 打印正在处理的任务及其优先级
        std::cout << "Processing task: " << currentTask.name << " (Priority: " << currentTask.priority << ")\n";
    }

    return 0;
}
```

输出：

```
Processing task: Task2 (Priority: 1)
Processing task: Task3 (Priority: 2)
Processing task: Task1 (Priority: 3)
Processing task: Task5 (Priority: 4)
Processing task: Task4 (Priority: 5)
```

在这个示例中，我们定义了一个名为 `Task` 的结构体，它包含任务的名称和优先级。我们还重载了小于运算符，以便在优先级队列中按照优先级进行排序。

然后，我们创建了一个 `std::priority_queue<Task>` 对象，并添加了一些任务。在主循环中，我们不断地从优先级队列中取出优先级最高的任务进行处理，直到队列为空。

这个示例展示了 `std::priority_queue` 在任务调度等需要处理优先级场景中的实际应用。根据具体需求，可以自定义任务结构体以及优先级的比较方式。