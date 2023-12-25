# C++中的类函数

## 1. 问题

### 1.1 构造函数为什么不能为虚函数？

1. **初始化顺序**：
   - 构造函数的主要任务是初始化对象，包括其基类和成员变量。构造函数的执行顺序是从最基类开始，然后按照声明顺序初始化成员变量。
   - 如果构造函数是虚的，那么在创建对象时就需要动态绑定，这与构造过程的固定顺序相矛盾。
2. **对象尚未完全构建**：
   - 在调用构造函数的过程中，对象还没有完全构建，特别是对于派生类对象，其派生部分还未被初始化。
   - 如果构造函数是虚的，那么在派生类构造函数执行之前，可能需要通过虚函数表调用基类的构造函数，但此时虚函数表尚未建立或不完整。
3. **语法限制**：
   - C++语言规范规定构造函数不能声明为虚函数。即使尝试这样做，编译器也会拒绝该声明。
4. **设计原则**：
   - 虚函数主要用于实现多态性，即根据对象的实际类型调用相应的函数。然而，在构造过程中，对象的类型是已知的（正在被构造的类型），因此不需要动态绑定。
5. **内存管理**：
   - 构造函数期间，对象的内存布局尚未完全确定，包括虚函数表指针（vptr）的位置和内容。如果构造函数是虚的，那么在对象尚未完全构建时就可能需要访问虚函数表，这可能导致未定义的行为。

因此，由于上述原因，C++中构造函数不能是虚函数。相反，为了正确销毁派生类对象，通常建议在基类中提供一个虚析构函数。这样，当通过基类指针删除派生类对象时，可以确保调用的是实际对象类型的析构函数。

### 1.2 类的普通成员函数和const成员函数可以重名吗?

在C++中，一个类的普通成员函数和const成员函数可以具有相同的名称，但它们必须有不同的参数列表（包括constness），以构成重载。这是因为当成员函数的参数列表（包括constness）相同时，编译器无法区分这两个函数，会导致编译错误。

以下是一个例子：

```c++
class MyClass {
public:
    void myFunction(int value) {
        // 普通成员函数
        std::cout << "Called non-const member function." << std::endl;
    }

    void myFunction(int value) const {
        // const成员函数
        std::cout << "Called const member function." << std::endl;
    }
};
```

在这个例子中，两个`myFunction`成员函数具有相同的名称和参数列表，因此会引发编译错误。为了正确地重载这两个函数，需要修改其中一个函数的参数列表，如下所示：

```c++
class MyClass {
public:
    void myFunction(int value) {
        // 普通成员函数
        std::cout << "Called non-const member function." << std::endl;
    }

    void myFunction(double value) const {
        // const成员函数，参数类型不同
        std::cout << "Called const member function." << std::endl;
    }
};
```

现在，这两个函数具有不同的参数列表，因此可以正确地重载并根据调用时的实际参数类型和对象的constness来选择调用哪个函数。

## 2. 分类

1. **普通成员函数：**
   + 成员函数在类的定义中声明，包括返回类型、函数名和参数列表。

```c++
class MyClass {
public:
    int getValue(); // 声明一个返回int类型的成员函数getValue
};
```

2. **const成员函数：**
   + 带有`const`后缀的成员函数承诺不修改对象的状态。

```c++
class MyClass {
public:
    int getValue() const; // 保证不修改对象状态的成员函数
};
```

3. **静态成员函数：**
   + 静态成员函数属于类，不与任何特定对象关联。它们通过类名而非对象来调用。

```c++
class MyClass {
public:
    static void staticFunc(); // 静态成员函数
};
MyClass::staticFunc(); // 通过类名调用
```

4. **虚函数和纯虚函数：**
   + 虚函数（使用`virtual`关键字声明）允许动态绑定和多态性。
   + 纯虚函数（使用`= 0`声明）是一个抽象接口，要求派生类必须提供其实现。

```c++
class Base {
public:
    virtual void display() = 0; // 纯虚函数，Base成为抽象基类
};

class Derived : public Base {
public:
    void display() override { // 实现Base的虚函数
        std::cout << "Derived class" << std::endl;
    }
};
```

5. **构造函数和析构函数：**
   + 构造函数用于初始化新创建的对象，其名称与类名相同。
   + 析构函数用于释放对象的资源，在对象生命周期结束时自动调用，其名称是在类名前加上`~`符号。

```c++
class MyClass {
public:
    MyClass() {} // 默认构造函数
    ~MyClass() {} // 默认析构函数
};
```

## 3. 重要函数

### 3.1 构造函数

1. **普通构造函数：**
   - 普通构造函数是用于初始化新创建的对象的函数。它的名称与类名相同，没有返回类型，并且通常负责设置对象的初始状态。

```c++
class MyClass {
public:
    MyClass(int value) { // 普通构造函数，接受一个int参数
        myValue = value;
    }

private:
    int myValue;
};
```

2. **默认构造函数：**
   + 默认构造函数是一种特殊的构造函数，它不需要任何参数。如果用户没有自定义构造函数，编译器会自动提供一个默认构造函数。

```c++
class MyClass {
public:
    MyClass() {} // 默认构造函数，不接受任何参数
};
```

3. **拷贝构造函数：**
   + 拷贝构造函数是一种特殊的构造函数，用于创建一个新对象作为现有对象的副本。它的参数是一个引用到同一类类型的现有对象。

```c++
class MyClass {
public:
    MyClass(const MyClass& other) { // 拷贝构造函数
        myValue = other.myValue;
    }

private:
    int myValue;
};
```

4. **移动构造函数：**
   + 移动构造函数是一种特殊的构造函数，用于从一个将要被销毁的对象中“移动”资源来初始化新对象。它的参数通常是一个右值引用到同一类类型的对象。

```c++
class MyClass {
public:
    MyClass(MyClass&& other) noexcept { // 移动构造函数
        myValue = std::move(other.myValue);
    }

private:
    int myValue;
};
```

### 3.2 赋值函数

虽然不是构造函数，但赋值运算符与构造函数密切相关，因为它也涉及到对象的状态复制。赋值运算符通常重载为成员函数。

```c++
class MyClass {
public:
    MyClass& operator=(const MyClass& other) { // 拷贝赋值运算符
        if (this != &other) {
            myValue = other.myValue;
        }
        return *this;
    }

    MyClass& operator=(MyClass&& other) noexcept { // 移动赋值运算符（C++11及以后版本）
        if (this != &other) {
            myValue = std::move(other.myValue);
        }
        return *this;
    }

private:
    int myValue;
};
```

### 3.3 析构函数

#### 3.3.1 普通析构函数

析构函数是一个特殊成员函数，当对象生命周期结束时自动调用，用于释放对象占用的资源。

```c++
class MyClass {
public:
    ~MyClass() { // 析构函数
        // 释放资源或执行清理操作
    }
};
```

#### 3.3.2 虚析构函数

虚析构函数是在C++中用于支持多态性和正确销毁派生类对象的特殊成员函数。当一个基类指针指向一个派生类对象，并且通过这个基类指针删除该对象时，如果没有声明虚析构函数，可能会导致派生类的资源没有被正确释放。

以下是关于虚析构函数的一些关键点：

1. **声明**：
   + 虚析构函数通过在基类的析构函数声明前加上`virtual`关键字来声明。

```c++
class Base {
public:
    virtual ~Base() {} // 声明虚析构函数
};
```

2. **作用**：
   - 当通过基类指针删除派生类对象时，如果基类的析构函数是虚函数，编译器会确保调用的是实际对象类型的析构函数，而不是仅仅调用基类的析构函数。

3. **继承**：
   - 一旦基类的析构函数被声明为虚函数，所有直接或间接派生的类的析构函数也会自动成为虚函数，即使它们没有显式地声明为虚函数。

4. **资源管理**：
   - 使用虚析构函数可以确保派生类的资源（如动态分配的内存、文件句柄等）在删除对象时得到正确的释放。

5. **避免悬挂指针**：
   - 如果不使用虚析构函数，可能会导致仅销毁了基类部分，而派生类部分未被销毁，这可能导致悬挂指针和其他未定义行为。

以下是一个简单的例子：

```c++
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called." << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived destructor called." << std::endl;
    }
};

int main() {
    Base* basePtr = new Derived();
    delete basePtr; // 正确调用虚析构函数

    return 0;
}
```

在这个例子中，由于`Base`类的析构函数是虚函数，所以在通过`basePtr`删除`Derived`对象时，首先调用`Derived`的析构函数，然后调用`Base`的析构函数。这样可以确保派生类和基类的所有资源都被正确释放。

## 4. 实战

### 4.1 实现MyString

```c++
#include <iostream>
#include <cstring>

class MyString {
public:
    // 默认构造函数
    MyString() : str(nullptr), size(0), capacity(0) {}

    // 普通构造函数
    MyString(const char* input) {
        size = std::strlen(input);
        capacity = size + 1;
        str = new char[capacity];
        std::strcpy(str, input);
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        size = other.size;
        capacity = other.capacity;
        str = new char[capacity];
        std::strcpy(str, other.str);
    }

    // 移动构造函数
    MyString(MyString&& other) noexcept {
        str = other.str;
        size = other.size;
        capacity = other.capacity;

        other.str = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    // 赋值运算符
    MyString& operator=(const MyString& other) {
        if (this != &other) { //防止自己赋值自己
            delete[] str;  //删除原有的空间

            size = other.size;
            capacity = other.capacity;
            str = new char[capacity];  //申请新空间
            std::strcpy(str, other.str);
        }
        return *this;
    }

    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {  //防止自己赋值自己
            delete[] str;  //删除原有的空间

            str = other.str;  //窃取对象other
            size = other.size;
            capacity = other.capacity;

            other.str = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 析构函数
    ~MyString() {
        delete[] str;
    }

    // 其他成员函数（例如访问器、修改器等）

private:
    char* str;
    size_t size;
    size_t capacity;
};

int main() {
    MyString s1("Hello, World!");
    MyString s2(s1); // 使用拷贝构造函数
    MyString s3("Goodbye, World!");
    s3 = s1; // 使用赋值运算符

    MyString s4(std::move(s2)); // 使用移动构造函数
    MyString s5("See you soon!");
    s5 = std::move(s4); // 使用移动赋值运算符

    return 0;
}
```

### 4.2 完整的MyString

```c++
#include <iostream>
#include <cstring>

class MyString {
public:
    // 默认构造函数
    MyString() : str(nullptr), size(0), capacity(0) {}

    // 普通构造函数
    MyString(const char* input) {
        size = std::strlen(input);
        capacity = size + 1;
        str = new char[capacity];
        std::strcpy(str, input);
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        size = other.size;
        capacity = other.capacity;
        str = new char[capacity];
        std::strcpy(str, other.str);
    }

    // 移动构造函数
    MyString(MyString&& other) noexcept {
        str = other.str;
        size = other.size;
        capacity = other.capacity;

        other.str = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    // 赋值运算符
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;

            size = other.size;
            capacity = other.capacity;
            str = new char[capacity];
            std::strcpy(str, other.str);
        }
        return *this;
    }

    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] str;

            str = other.str;
            size = other.size;
            capacity = other.capacity;

            other.str = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 析构函数
    ~MyString() {
        delete[] str;
    }

    // 访问器
    char operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return str[index];
    }

    char at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return str[index];
    }

    const char* c_str() const {
        return str;
    }

    size_t length() const {
        return size;
    }

    // 修改器
    void clear() {
        delete[] str;
        str = nullptr;
        size = 0;
        capacity = 0;
    }

    void resize(size_t newSize) {
        if (newSize > capacity) {
            reserve(newSize);
        }
        size = newSize;
        str[size] = '\0';
    }

    void reserve(size_t newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        char* newStr = new char[newCapacity];
        std::strcpy(newStr, str);
        delete[] str;
        str = newStr;
        capacity = newCapacity;
    }

    void assign(const char* input) {
        size = std::strlen(input);
        reserve(size + 1);
        std::strcpy(str, input);
    }

    void append(const MyString& other) {
        size_t newLength = size + other.size;
        reserve(newLength + 1);
        std::strcpy(str + size, other.str);
        size = newLength;
        str[size] = '\0';
    }

    void prepend(const MyString& other) {
        size_t newLength = size + other.size;
        reserve(newLength + 1);
        memmove(str + other.size, str, size + 1);
        std::strcpy(str, other.str);
        size = newLength;
    }

private:
    char* str;
    size_t size;
    size_t capacity;
};

int main() {
    MyString s1("Hello, World!");
    MyString s2(s1); // 使用拷贝构造函数
    MyString s3("Goodbye, World!");
    s3 = s1; // 使用赋值运算符

    MyString s4(std::move(s2)); // 使用移动构造函数
    MyString s5("See you soon!");
    s5 = std::move(s4); // 使用移动赋值运算符

    std::cout << s1.length() << std::endl;
    std::cout << s1.c_str() << std::endl;
    std::cout << s1[6] << std::endl;

    s1.append(s3);
    std::cout << s1.c_str() << std::endl;

    return 0;
}
```

## 5. 补充知识

### 5.1 函数重载条件

在C++中，函数重载（Overloading）是指在一个作用域内，可以有多个同名的函数，但它们必须具有不同的参数列表。以下是函数重载需要满足的条件：

1. **相同的作用域**：
   - 函数重载必须在同一作用域内，例如在同一类或同一命名空间中。
2. **相同的函数名称**：
   - 重载的函数必须具有相同的名称。
3. **不同的参数列表**：
   - 参数列表的不同可以体现在以下方面：
     - 参数的数量（arity）不同。
     - 参数的类型不同。
     - 参数的顺序不同。

注意以下几点：

- 函数的返回类型不能用于区分重载函数，也就是说，仅仅返回类型不同而参数列表相同的函数不能构成重载。
- 函数的访问修饰符（public、private、protected）不影响重载，因为访问修饰符不是函数签名的一部分。
- 引用和指针类型作为参数时，const和volatile限定符会影响重载，因为它们是类型的一部分。

以下是一个函数重载的例子：

```c++
class MyClass {
public:
    void myFunction(int value) {
        // 处理int类型的值
    }

    void myFunction(double value) {
        // 处理double类型的值
    }

    void myFunction(int value1, int value2) {
        // 处理两个int类型的值
    }
};
```

