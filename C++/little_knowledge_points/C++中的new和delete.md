# C++中的new和delete

## 1. 问题

### 1.1 new分配的内存用free来释放会产生的后果？

使用`free`来释放由`new`分配的内存会导致未定义的行为，可能会产生以下一些后果：

1. **程序崩溃**：
   - 因为`new`和`delete`在分配和释放内存时可能使用了不同的内部数据结构和算法，而`malloc`和`free`也有自己的管理方式。混用它们可能导致这些数据结构的不匹配，进而引发程序崩溃。
2. **内存泄漏**：
   - 当使用`free`释放`new`分配的内存时，对象的析构函数不会被调用。如果对象在构造过程中分配了其他资源（如文件描述符、网络连接等），这些资源将无法被正确释放，导致内存泄漏。
3. **数据损坏**：
   - `free`释放内存后，该内存区域可能被操作系统重新分配给其他进程或线程使用。如果后续代码继续访问已被释放的内存，可能会导致数据损坏或安全漏洞。

以下是一个例子：

```c++
#include <iostream>

int main() {
    int* ptr = new int(5);  // 使用new分配一个int类型的内存

    std::cout << "*ptr: " << *ptr << std::endl;

    free(ptr);  // 错误地使用free释放内存

    std::cout << "*ptr: " << *ptr << std::endl;  // 这里访问已释放的内存，结果是未定义的

    delete ptr;  // 这里试图删除已经被free释放的内存，也是错误的

    return 0;
}
```

在这个例子中，首先使用`new`分配了一个整数并初始化为5。然后错误地使用`free`来释放内存，接着再次尝试访问和删除这个内存。由于这些操作违反了C++的内存管理规则，程序的行为是未定义的，可能会导致崩溃、内存泄漏或其他不可预知的问题。

### 1.2 malloc申请的内存用delete来删除的后果?

使用`delete`来释放由`malloc`分配的内存也会导致未定义的行为，可能会产生以下一些后果：

1. **程序崩溃**：
   - `malloc`和`free`是C语言中的内存管理函数，它们不处理对象的构造和析构。而`delete`是C++中的运算符，它在释放内存之前会调用对象的析构函数。如果尝试使用`delete`释放由`malloc`分配的原始内存，可能会因为试图执行不存在的析构函数而导致程序崩溃。
2. **内存泄漏**：
   - 类似于使用`free`释放`new`分配的内存，使用`delete`释放`malloc`分配的内存也不会调用对象的析构函数。如果对象在构造过程中分配了其他资源，这些资源将无法被正确释放，导致内存泄漏。
3. **数据损坏**：
   - 同样，当使用错误的内存管理函数释放内存后，该内存区域可能被操作系统重新分配给其他进程或线程使用。如果后续代码继续访问已被释放的内存，可能会导致数据损坏或安全漏洞。

以下是一个例子：

```c++
#include <iostream>

int main() {
    int* ptr = static_cast<int*>(malloc(sizeof(int)));  // 使用malloc分配一个int类型的内存

    if (ptr != nullptr) {
        *ptr = 5;
        std::cout << "*ptr: " << *ptr << std::endl;

        delete ptr;  // 错误地使用delete释放内存

        std::cout << "*ptr: " << *ptr << std::endl;  // 这里访问已删除的内存，结果是未定义的
    }

    return 0;
}
```

在这个例子中，首先使用`malloc`分配了一个整数的内存，并将其初始化为5。然后错误地使用`delete`来释放内存，接着再次尝试访问这个内存。由于这些操作违反了C++的内存管理规则，程序的行为是未定义的，可能会导致崩溃、内存泄漏或其他不可预知的问题。

## 2. 基础知识

在C++中，`new`和`delete`是用于动态内存管理的关键字。它们允许你在程序运行时动态地创建和销毁对象。

1. **new运算符**：

   - `new`关键字用于动态分配内存以存储对象或数组。以下是一些基本用法：

     ```c++
     // 分配单个对象的内存
     int* p = new int;  // 分配一个int类型的内存，并返回指向该内存的指针
     std::string* str = new std::string("Hello");  // 分配一个std::string对象，并初始化为"Hello"
     
     // 分配数组的内存
     int* arr = new int[5];  // 分配一个包含5个int元素的数组
     std::string* strArr = new std::string[3];  // 分配一个包含3个std::string对象的数组
     ```

     在使用`new`分配内存后，你需要确保在适当的时候释放这些内存。

2. **delete运算符**：

   - `delete`关键字用于释放之前通过`new`分配的内存。以下是如何使用`delete`：

     ```c++
     // 删除单个对象
     delete p;  // 释放p指向的内存
     delete str;  // 释放str指向的内存
     
     // 删除数组
     delete[] arr;  // 释放arr指向的整个数组的内存
     delete[] strArr;  // 释放strArr指向的整个数组的内存
     ```

     在释放内存后，最好将指针设置为`nullptr`，以防止出现悬挂指针（dangling pointer）问题。

```c++
p = nullptr;
arr = nullptr;
str = nullptr;
strArr = nullptr;
```

注意事项：

- 动态分配的内存如果没有被正确释放，会导致内存泄漏。
- 使用`new`分配的对象或数组需要与`delete`或`delete[]`匹配使用。对于单个对象使用`delete`，对于数组使用`delete[]`。
- 如果在`new`操作失败（例如，因为没有足够的内存），它会返回`nullptr`。因此，在使用新分配的内存之前，你应该检查指针是否为`nullptr`。
- C++11及以后的标准引入了智能指针（如`std::unique_ptr`、`std::shared_ptr`等），它们可以自动管理所指向的对象的生命周期，从而减少手动使用`new`和`delete`的需求并降低错误的可能性。

## 3. 和malloc/free的区别

C++中的`new`和`delete`是面向对象的内存管理运算符，而`malloc`和`free`是C语言中的原始内存管理函数。以下是它们的主要区别和例子：

1. **类型安全**：
   - `new`和`delete`是类型安全的，编译器会根据指针的类型来分配和释放相应的内存。
   - `malloc`和`free`不检查类型，只处理字节级别的内存。
2. **构造函数和析构函数**：
   - `new`在分配内存后会调用相应的构造函数初始化对象。
   - `delete`在释放内存前会调用对象的析构函数。
   - `malloc`和`free`不涉及构造函数和析构函数的调用。
3. **重载**：
   - `new`和`delete`可以被用户自定义的运算符重载。
   - `malloc`和`free`不能被重载。
4. **使用语法**：
   - `new`和`delete`是运算符，使用起来更符合C++的语境。
   - `malloc`和`free`是库函数，需要包含 `<cstdlib>` 头文件。

以下是一些例子：

```c++
// 使用new和delete
#include <iostream>

struct MyClass {
    int value;
    MyClass(int v) : value(v) { std::cout << "Constructor called for " << value << std::endl; }
    ~MyClass() { std::cout << "Destructor called for " << value << std::endl; }
};

int main() {
    MyClass* obj = new MyClass(10);  // 分配内存并调用构造函数
    std::cout << "obj->value: " << obj->value << std::endl;
    delete obj;  // 调用析构函数并释放内存

    return 0;
}
cpp
// 使用malloc和free
#include <cstdlib>
#include <iostream>

struct MyClass {
    int value;
    MyClass(int v) : value(v) { std::cout << "Constructor called for " << value << std::endl; }
    ~MyClass() { std::cout << "Destructor called for " << value << std::endl; }
};

int main() {
    MyClass* obj = static_cast<MyClass*>(std::malloc(sizeof(MyClass)));  // 分配内存，但不会调用构造函数
    if (obj != nullptr) {
        new (obj) MyClass(10);  // 手动调用构造函数
        std::cout << "obj->value: " << obj->value << std::endl;
        obj->~MyClass();  // 手动调用析构函数
        std::free(obj);  // 释放内存
    }

    return 0;
}
```

在上述例子中，`new`和`delete`的例子更简洁且自动管理了构造函数和析构函数的调用。而`malloc`和`free`的例子需要手动调用构造函数和析构函数，并且没有类型检查。在现代C++编程中，通常推荐使用`new`和`delete`或智能指针来管理内存，而不是直接使用`malloc`和`free`。