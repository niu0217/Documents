# C++中的static

## 1. 问题

### 1.1 类中的static可以继承吗？

在C++中，类中的静态成员（用`static`关键字修饰的）并不是继承的组成部分。也就是说，静态成员不会被派生类继承。

但是，派生类可以访问基类的静态成员，只要它们具有足够的访问权限（公共或受保护）。这是因为静态成员属于类本身，而不是类的实例，所以无论创建多少个类的对象，静态成员都只有一份拷贝。

以下几点关于静态成员和继承的要点：

1. 基类的静态成员变量在派生类中仍然可以通过基类名进行访问。
2. 派生类不能重新定义基类的静态成员，但可以声明自己的静态成员。
3. 如果基类的静态成员在派生类的作用域内被访问，需要使用作用域解析运算符(`::`)来明确指定是基类的静态成员。

总的来说，虽然静态成员不直接参与继承，但派生类可以通过适当的方式访问和使用基类的静态成员。

### 1.2 static有哪些应用场景？

在C++中，`static`关键字具有多种用途，以下是一些主要的应用场景：

1. **静态局部变量**：
   - 当你在函数内部声明一个静态局部变量时，该变量只会被初始化一次，且其值在函数调用之间保持不变。
   - 即使函数结束，静态局部变量的值也不会被销毁，下次函数调用时会保留上次的值。
2. **静态全局变量**：
   - 在文件作用域（全局作用域）声明的静态变量只在该编译单元（通常是一个源文件）内可见。
   - 静态全局变量在程序开始运行时进行初始化，并在程序结束时销毁。
3. **静态数据成员**：
   - 在类中声明的静态数据成员是属于整个类的，而不是属于类的某个对象。
   - 静态数据成员需要在类外部定义和初始化，且在整个程序中只有一个副本。
   - 所有类的对象共享同一个静态数据成员的值。
4. **静态成员函数**：
   - 静态成员函数属于类，而不属于类的任何特定对象。
   - 静态成员函数只能访问静态数据成员和其他静态成员函数，不能访问类的非静态成员。
5. **内部链接**：
   - 在函数或类内部声明的静态函数或变量默认具有内部链接（也称为静态链接），这意味着它们只在当前编译单元内可见，不会与其它编译单元中的同名符号冲突。
6. **隐式类型转换限制**：
   - 当用于构造函数前时，`explicit`关键字阻止了该构造函数进行隐式类型转换。这有助于避免意外的类型转换。

注意，`static`的关键字使用可能会根据上下文和具体需求有所不同。在不同的情况下，`static`的作用和行为也会有所变化。

## 2. 实战代码

### 2.1 静态局部变量

```c++
#include <iostream>

void function() {
    static int count = 0; // 静态局部变量

    std::cout << "This function has been called " << ++count << " times." << std::endl;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        function();
    }
    return 0;
}
```

在这个例子中，`function()`每次被调用时，`count`的值都会增加，因为它是静态局部变量。

### 2.2 静态全局变量

```c++
// file1.cpp
static int globalVar = 0; // 静态全局变量

void incrementGlobal() {
    ++globalVar;
}
```

```c++
// file2.cpp
extern void incrementGlobal(); // 声明incrementGlobal函数

int main() {
    incrementGlobal();
    incrementGlobal();
    return 0;
}
```

在这个例子中，`globalVar`是静态全局变量，只在`file1.cpp`中可见。但仍然可以通过`incrementGlobal()`函数修改它的值。

### 2.3 静态数据成员

```c++
class MyClass {
public:
    static int classCount; // 静态数据成员声明

    MyClass() {
        ++classCount;
    }
};

int MyClass::classCount = 0; // 静态数据成员定义和初始化

int main() {
    MyClass obj1;
    MyClass obj2;
    MyClass obj3;

    std::cout << "Number of MyClass objects created: " << MyClass::classCount << std::endl;
    return 0;
}
```

在这个例子中，每次创建新的对象的时候，classCount就会+1。

### 2.4 静态成员函数

```c++
class MyClass {
private:
    static int totalObjects;

public:
    MyClass() {
        ++totalObjects;
    }

    static int getTotalObjects() { // 静态成员函数
        return totalObjects;
    }
};

int MyClass::totalObjects = 0;

int main() {
    MyClass obj1;
    MyClass obj2;
    MyClass obj3;

    std::cout << "Total number of MyClass objects: " << MyClass::getTotalObjects() << std::endl;
    return 0;
}
```

在这个例子中，`getTotalObjects()`是一个静态成员函数，它可以访问和返回静态数据成员`totalObjects`的值，而不需要任何类的对象。