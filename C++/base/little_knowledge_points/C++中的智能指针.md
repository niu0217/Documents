# C++中的智能指针

## 1. 问题

## 2. 基本知识

C++中的智能指针是一种对象，它存储了对动态分配的对象的指针，并在适当的时候自动删除该对象。智能指针的主要目的是管理动态内存，以防止内存泄漏和悬挂指针的问题。

C++11及以后的标准中提供了三种主要的智能指针类型：

1. unique_ptr：
   - unique_ptr是独占所有权的智能指针，一个unique_ptr对象在任何时候都拥有它所指向的对象的所有权。
   - 当unique_ptr对象被销毁（例如，离开作用域或被赋值给另一个unique_ptr）时，它会自动删除它所指向的对象。
   - unique_ptr不支持拷贝构造函数和赋值操作符，但支持移动构造函数和移动赋值操作符。

```c++
#include <memory>

std::unique_ptr<int> ptr = std::make_unique<int>(10);  // 创建一个unique_ptr，指向新分配的int对象

// 使用*
std::cout << "*ptr: " << *ptr << std::endl;

// 使用->
std::cout << "ptr->value: " << ptr->value << std::endl;
```

2. shared_ptr：

   - shared_ptr是共享所有权的智能指针，多个shared_ptr对象可以同时拥有并共享同一个对象的所有权。

   - 每个shared_ptr对象都维护一个计数器，记录有多少个shared_ptr对象指向同一个对象。

   - 当最后一个共享同一对象的shared_ptr被销毁时，该对象会被自动删除。

```c++
#include <memory>

std::shared_ptr<int> ptr1 = std::make_shared<int>(10);  // 创建一个shared_ptr，指向新分配的int对象

std::shared_ptr<int> ptr2 = ptr1;  // ptr2现在也共享ptr1指向的对象

// 使用*
std::cout << "*ptr1: " << *ptr1 << std::endl;
std::cout << "*ptr2: " << *ptr2 << std::endl;

// 使用->
std::cout << "ptr1.use_count(): " << ptr1.use_count() << std::endl;  // 输出共享该对象的shared_ptr数量
```

3. weak_ptr：

   - weak_ptr是为了配合shared_ptr而设计的，它不增加对象的引用计数，因此不会阻止对象的删除。

   - weak_ptr主要用于解决shared_ptr之间的循环引用问题。

```c++
#include <memory>

std::shared_ptr<Node> node1 = std::make_shared<Node>();
std::shared_ptr<Node> node2 = std::make_shared<Node>();

node1->next = node2;
node2->prev = node1;  // 循环引用

// 使用weak_ptr打破循环引用
std::weak_ptr<Node> weakNode1 = node1;
node2->prev = weakNode1;
```

总的来说，智能指针通过自动管理内存，提高了代码的安全性和可维护性。在现代C++编程中，通常推荐使用智能指针而不是原始的裸指针来管理动态内存。

## 3. 使用shared_ptr

### 3.1 例子一

```c++
#include <iostream>
#include <memory>

// 定义一个简单的类
class MyClass {
public:
    MyClass(int value) : value_(value) {
        std::cout << "MyClass constructor called with value: " << value_ << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor called for value: " << value_ << std::endl;
    }

    int getValue() const {
        return value_;
    }

private:
    int value_;
};

int main() {
    // 使用make_shared创建并初始化一个shared_ptr
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(10);

    // 访问和修改对象的值
    std::cout << "Value from ptr: " << ptr->getValue() << std::endl;
    std::cout<<"ptr count: "<<ptr.use_count()<<std::endl;

    // 创建另一个shared_ptr，共享同一个对象
    std::shared_ptr<MyClass> anotherPtr(ptr);
    std::cout<<"ptr count: "<<ptr.use_count()<<std::endl;
    std::cout<<"anotherPtr count: "<<anotherPtr.use_count()<<std::endl;

    // 当ptr和anotherPtr都离开作用域时，它们会自动删除共享的对象
    // 因为它们的引用计数都变为0

    return 0;
}
```

输出：

```
MyClass constructor called with value: 10
Value from ptr: 10
ptr count: 1
ptr count: 2
anotherPtr count: 2
MyClass destructor called for value: 10
```

### 3.2 例子二

```c++
#include <iostream>
#include <memory>

class Node {
public:
    int value;
    std::shared_ptr<Node> next;

    Node(int value) : value(value), next(nullptr) {
        std::cout << "Node constructor called with value: " << value << std::endl;
    }

    ~Node() {
        std::cout << "Node destructor called for value: " << value << std::endl;
    }
};

int main() {
    // 创建两个节点
    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);

    // 创建环形引用
    node1->next = node2;
    node2->next = node1;  // 此时形成了循环引用

    return 0;
}
```

在这个例子中，我们定义了一个简单的类`Node`，它有一个整数值和一个指向另一个`Node`对象的`std::shared_ptr`。在`main`函数中，我们创建了两个`Node`对象`node1`和`node2`，然后让它们互相引用，形成了一个环形引用。

当`node1`和`node2`离开作用域时，由于它们互相引用，各自的引用计数都不会变为0，因此它们所指向的`Node`对象不会被自动删除。这会导致内存泄漏。

要解决这个问题，可以使用`std::weak_ptr`来打破环形引用。`std::weak_ptr`不增加对象的引用计数，因此不会阻止对象的删除。在上述代码中，可以将其中一个`next`成员改为`std::weak_ptr`，如下所示：

```c++
class Node {
public:
    int value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // 改为 weak_ptr

    // ...
};
```

然后在创建环形引用时，将一个方向的引用改为`std::weak_ptr`：

```c++
node1->next = node2;
node2->prev = std::weak_ptr<Node>(node1);  // 使用 weak_ptr 打破循环引用
```

这样，当所有持有`Node`对象的`std::shared_ptr`都被销毁后，`Node`对象会被自动删除，解决了环形引用导致的内存泄漏问题。

### 3.3 例子三(全能)

```c++
#include <iostream>
#include <memory>
#include <vector>

// 定义一个简单的类
class MyClass {
public:
    MyClass(int value) : value_(value) {
        std::cout << "MyClass constructor called with value: " << value_ << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor called for value: " << value_ << std::endl;
    }

    int getValue() const {
        return value_;
    }

private:
    int value_;
};

int main() {
    // 创建并初始化一个shared_ptr
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(10);

    // 访问和修改对象的值
    std::cout << "Value from ptr: " << ptr->getValue() << std::endl;

    // 创建另一个shared_ptr，共享同一个对象
    std::shared_ptr<MyClass> anotherPtr(ptr);

    // 使用use_count查看引用计数
    std::cout << "ptr use count: " << ptr.use_count() << std::endl;
    std::cout << "anotherPtr use count: " << anotherPtr.use_count() << std::endl;

    // 使用reset删除当前对象并设置新的对象
    ptr.reset(new MyClass(20));
    std::cout << "Value after reset: " << ptr->getValue() << std::endl;
    std::cout << "ptr use count: " << ptr.use_count() << std::endl;
    std::cout << "anotherPtr use count: " << anotherPtr.use_count() << std::endl;

    // 使用get获取原始指针
    MyClass* rawPtr = ptr.get();
    std::cout << "Value from raw pointer: " << rawPtr->getValue() << std::endl;

    // 使用swap交换两个shared_ptr的所有权
    std::shared_ptr<MyClass> thirdPtr(new MyClass(30));
    std::shared_ptr<MyClass> another_thirdptr(thirdPtr);
    ptr.swap(thirdPtr);
    std::cout << "Value after swap (ptr): " << ptr->getValue() << std::endl;
    std::cout << "Value after swap (thirdPtr): " << thirdPtr->getValue() << std::endl;
    std::cout << "ptr use count: " << ptr.use_count() << std::endl;
    std::cout << "thirdPtr count: " << thirdPtr.use_count() << std::endl;

    // 使用动态数组
    std::shared_ptr<int[]> arrPtr(new int[5]{1, 2, 3, 4, 5});
    std::cout << "Array element [2]: " << arrPtr[2] << std::endl;

    // 使用shared_ptr与容器
    std::vector<std::shared_ptr<MyClass>> vec;
    vec.push_back(std::make_shared<MyClass>(50));
    vec.push_back(anotherPtr);

    // 输出所有元素的值
    for (const auto& elem : vec) {
        std::cout << "Value from vector: " << elem->getValue() << std::endl;
    }

    return 0;
}
```

这个示例中使用了以下`std::shared_ptr`相关的函数和操作：

- `std::make_shared`：创建并初始化一个`std::shared_ptr`对象。
- `getValue`和`->`操作符：访问和修改对象的成员。
- `use_count`：查看引用计数。
- `reset`：删除当前对象并设置新的对象。
- `get`：获取原始指针。
- `swap`：交换两个`std::shared_ptr`的所有权。
- 动态数组的支持：使用`std::shared_ptr`管理动态分配的数组。
- `std::shared_ptr`与容器（如`std::vector`）的结合使用。

这个示例展示了`std::shared_ptr`的一些常见用法和功能。在实际编程中，应根据具体需求选择合适的操作和函数。

## 4. 使用weak_ptr

```c++
#include <iostream>
#include <memory>

// 定义一个简单的类
class MyClass {
public:
    MyClass(int value) : value_(value) {
        std::cout << "MyClass constructor called with value: " << value_ << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor called for value: " << value_ << std::endl;
    }

    int getValue() const {
        return value_;
    }

private:
    int value_;
};

int main() {
    // 创建并初始化一个shared_ptr
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(10);

    // 创建一个weak_ptr，它不增加引用计数
    std::weak_ptr<MyClass> weakPtr(sharedPtr);

    // 使用lock获取可访问的对象（如果仍然存在）
    if (std::shared_ptr<MyClass> lockedPtr = weakPtr.lock()) {
        std::cout << "Value from lockedPtr: " << lockedPtr->getValue() << std::endl;
    } else {
        std::cout << "Object has been deleted." << std::endl;
    }

    // 清空shared_ptr，删除对象
    sharedPtr.reset();

    // 再次尝试lock，此时对象已被删除
    if (std::shared_ptr<MyClass> lockedPtr = weakPtr.lock()) {
        std::cout << "Value from lockedPtr: " << lockedPtr->getValue() << std::endl;
    } else {
        std::cout << "Object has been deleted." << std::endl;
    }

    // 使用expired检查对象是否已被删除
    if (weakPtr.expired()) {
        std::cout << "Object has been deleted (expired)." << std::endl;
    } else {
        std::cout << "Object still exists." << std::endl;
    }

    // 使用reset释放weak_ptr
    weakPtr.reset();

    return 0;
}
```

输出：

```
MyClass constructor called with value: 10
Value from lockedPtr: 10
MyClass destructor called for value: 10
Object has been deleted.
Object has been deleted (expired).
```

这个示例中使用了以下`std::weak_ptr`相关的函数和操作：

- 创建`std::weak_ptr`：通过将`std::shared_ptr`传递给`std::weak_ptr`的构造函数来创建一个`std::weak_ptr`。
- `lock`：尝试获取一个可访问的`std::shared_ptr`。如果原始对象仍然存在，返回一个有效的`std::shared_ptr`；否则，返回一个空的`std::shared_ptr`。
- `expired`：检查`std::weak_ptr`所指向的对象是否已被删除。如果是，则返回`true`；否则，返回`false`。
- `reset`：释放`std::weak_ptr`，使其不再指向任何对象。

这个示例展示了`std::weak_ptr`的一些常见用法和功能。在实际编程中，`std::weak_ptr`通常用于打破循环引用或者在不需要拥有对象所有权的情况下访问对象。

## 5. 使用unique_ptr

```c++
#include <iostream>
#include <memory>

// 定义一个简单的类
class MyClass {
public:
    MyClass(int value) : value_(value) {
        std::cout << "MyClass constructor called with value: " << value_ << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor called for value: " << value_ << std::endl;
    }

    int getValue() const {
        return value_;
    }

private:
    int value_;
};

int main() {
    // 创建并初始化一个unique_ptr
    std::unique_ptr<MyClass> uniquePtr(new MyClass(10));

    // 访问和修改对象的值
    std::cout << "Value from uniquePtr: " << uniquePtr->getValue() << std::endl;

    // 使用release放弃所有权但不删除对象
    MyClass* rawPtr = uniquePtr.release();

    // 使用reset删除当前对象并设置新的对象
    uniquePtr.reset(new MyClass(20));
    std::cout << "Value after reset: " << uniquePtr->getValue() << std::endl;

    // 使用get获取原始指针
    MyClass* anotherRawPtr = uniquePtr.get();
    std::cout << "Value from anotherRawPtr: " << anotherRawPtr->getValue() << std::endl;

    // 使用swap交换两个unique_ptr的所有权
    std::unique_ptr<MyClass> anotherUniquePtr(new MyClass(30));
    std::swap(uniquePtr, anotherUniquePtr);
    std::cout << "Value after swap (uniquePtr): " << uniquePtr->getValue() << std::endl;
    std::cout << "Value after swap (anotherUniquePtr): " << anotherUniquePtr->getValue() << std::endl;

    // 使用make_unique创建并初始化一个unique_ptr
    uniquePtr = std::make_unique<MyClass>(40);
    std::cout << "Value after make_unique: " << uniquePtr->getValue() << std::endl;

    // 使用动态数组
    std::unique_ptr<int[]> arrPtr(new int[5]{1, 2, 3, 4, 5});
    std::cout << "Array element [2]: " << arrPtr[2] << std::endl;

    // 删除原始指针
    delete rawPtr;

    return 0;
}
```

输出：

```
MyClass constructor called with value: 10
Value from uniquePtr: 10
MyClass constructor called with value: 20
Value after reset: 20
Value from anotherRawPtr: 20
MyClass constructor called with value: 30
Value after swap (uniquePtr): 30
Value after swap (anotherUniquePtr): 20
MyClass constructor called with value: 40
MyClass destructor called for value: 30
Value after make_unique: 40
Array element [2]: 3
MyClass destructor called for value: 10
MyClass destructor called for value: 20
MyClass destructor called for value: 40
```

这个示例中使用了以下`std::unique_ptr`相关的函数和操作：

- 创建`std::unique_ptr`：通过将新分配的对象传递给`std::unique_ptr`的构造函数来创建一个`std::unique_ptr`。
- `getValue`和`->`操作符：访问和修改对象的成员。
- `release`：放弃所有权但不删除对象，返回原始指针。
- `reset`：删除当前对象并设置新的对象（如果提供了参数）。
- `get`：获取原始指针。
- `swap`：交换两个`std::unique_ptr`的所有权。
- `make_unique`：创建并初始化一个`std::unique_ptr`对象。
- 动态数组的支持：使用`std::unique_ptr`管理动态分配的数组。

这个示例展示了`std::unique_ptr`的一些常见用法和功能。在实际编程中，`std::unique_ptr`通常用于确保资源（如动态分配的对象）在其生命周期结束时被正确删除。由于`std::unique_ptr`不支持拷贝和赋值，它强调了资源的所有权唯一性。
