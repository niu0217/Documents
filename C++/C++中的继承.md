# C++中的继承

## 1. 问题

### 1.1 私有继承的用意？

在C++中，私有继承意味着基类的公共和保护成员在派生类中变为私有成员。因此，以下是如何使用私有继承的类：

**（1）访问基类的公有和保护成员**：

- 在派生类内部，你可以直接访问基类的公有和保护成员，因为它们现在是派生类的私有成员。
- 但是，你不能通过派生类的对象或指针从派生类的外部访问这些成员。

```c++
class Base {
public:
    void publicFunc() {}
protected:
    void protectedFunc() {}
private:
    void privateFunc() {} // 不可访问
};

class Derived : private Base {
public:
    void derivedFunc() {
        publicFunc(); // 可以直接访问基类的公有和保护成员
        protectedFunc();
    }
};
```

**（2）使用基类的方法**：

+ 如果你需要在派生类中调用基类的某个方法，你可以直接使用作用域解析运算符（`::`）来调用。

```c++
class Derived : private Base {
public:
    void derivedFunc() {
        Base::publicFunc(); // 使用作用域解析运算符调用基类的方法
    }
};
```

**（3）转换为基类类型**：

+ 由于私有继承不允许派生类对象被视为基类对象，所以你不能直接将派生类对象转换为基类类型。

- 然而，在某些特殊情况下，你可能需要在派生类内部强制转换为基类类型。这通常是为了实现某种设计策略，但应该谨慎使用。

```c++
class Derived : private Base {
public:
    void derivedFunc() {
        Base& baseRef = static_cast<Base&>(*this); // 在派生类内部强制转换为基类引用
        baseRef.publicFunc();
    }
};
```

**（4）友元关系**：

+ 如果基类和派生类之间存在友元关系，那么友元类可以访问派生类中的基类成员。

```c++
class FriendClass;

class Base {
    friend class FriendClass;
    // ...
};

class Derived : private Base {
    // ...
};

class FriendClass {
public:
    void accessDerived(Derived& derived) {
        derived.publicFunc(); // 友元类可以直接访问派生类中的基类成员
    }
};
```

总的来说，私有继承主要用于实现特定的设计模式或者封装基类的实现细节。由于它限制了外部代码对基类成员的访问，所以在使用私有继承时需要确保你的设计意图与这种限制相符合。

### 1.2 受保护继承的用意？

受保护继承在C++中的用意主要是为了限制对基类成员的访问，同时允许派生类及其子类访问这些成员。以下是受保护继承的一些主要特点和用意：

1. **访问权限变化**：
   - 在受保护继承中，基类的公共成员在派生类中变为保护成员。
   - 基类的保护成员在派生类中保持为保护成员。
2. **限制外部访问**：
   - 与私有继承类似，受保护继承也限制了外部代码对基类成员的直接访问。
   - 外部代码不能通过派生类的对象或指针访问基类的公共和保护成员。
3. **支持子类扩展**：
   - 受保护继承允许派生类及其子类访问基类的保护成员。
   - 这意味着派生类可以基于基类的功能进行扩展，并且这些扩展可能对派生类的子类可见。
4. **实现细节封装**：
   - 受保护继承可以用于封装基类的实现细节，防止外部代码直接修改或依赖于这些细节。
   - 同时，它允许派生类在必要时访问和使用这些实现细节。
5. **设计灵活性**：
   - 受保护继承提供了一种中间访问级别，介于公有继承和私有继承之间。
   - 它为设计者提供了更多的灵活性，可以根据具体需求选择最适合的继承方式。

```c++
class Base {
protected:
    void protectedFunc() {}
};

class Derived : protected Base {
public:
    void derivedFunc() {
        protectedFunc(); // 派生类可以访问基类的保护成员
    }
};

class DerivedChild : public Derived {
public:
    void childFunc() {
        protectedFunc(); // 派生类的子类也可以访问基类的保护成员
    }
};

int main() {
    Derived d;
    d.protectedFunc(); // 错误：外部代码不能访问基类的保护成员

    DerivedChild dc;
    dc.protectedFunc(); // 错误：外部代码不能访问基类的保护成员
}
```

在这个例子中，`Derived`类通过受保护继承`Base`类，使得`protectedFunc()`在`Derived`及其子类中变为保护成员。外部代码无法直接访问这个函数，但`Derived`和它的子类可以。这有助于封装基类的实现细节，同时允许派生类进行适当的扩展。

### 1.3 继承的注意事项？

在C++中使用继承时，以下是一些需要注意的事项：

1. **合理选择继承方式**：
   - 公有继承（public inheritance）表示“is-a”关系，例如，“Dog is a Animal”。
   - 私有继承（private inheritance）通常用于实现基于已存在类的接口，而不是表示类型之间的关系。
   - 受保护继承（protected inheritance）介于公有和私有之间，限制了外部对基类成员的访问。
2. **理解并遵循Liskov替换原则**：
   - 派生类对象应能够在任何期望使用基类对象的地方替代基类对象，而不改变程序的行为。
3. **避免不必要的继承**：
   - 不要为了代码重用而随意使用继承。考虑是否可以使用组合（has-a关系）或依赖关系代替。
4. **处理构造函数和析构函数**：
   - 构造函数和析构函数不会被继承，每个类都需要自己的构造函数和析构函数。
   - 在派生类的构造函数中，必须通过初始化列表调用基类的构造函数来初始化基类的部分。
5. **注意虚函数和多态**：
   - 如果希望派生类能够覆盖基类的行为，应在基类中声明虚函数（使用`virtual`关键字）。
   - 当基类的析构函数是虚函数时，可以确保通过基类指针删除派生类对象时正确地调用派生类的析构函数。
6. **理解访问权限**：
   - 派生类可以访问基类的公共和保护成员，但不能访问基类的私有成员。
   - 基类的私有成员在派生类中不可见，即使派生类继承了它们。
7. **防止对象切割（Slicing）**：
   - 当一个派生类的对象赋值给基类的对象或者通过基类的指针或引用创建派生类的对象时，可能会发生对象切割，即派生类的额外特性被忽略。为避免这种情况，应尽量使用指针或引用来操作对象。
8. **处理钻石继承问题**：
   - 当一个类从两个或多个间接相关的基类继承时，可能会出现钻石继承问题，导致数据成员或虚函数有多份拷贝。使用虚拟继承（在基类前加上`virtual`关键字）可以解决这个问题。
9. **谨慎使用多重继承**：
   - 多重继承可以增加类的复杂性，需要小心设计以避免二义性和维护问题。
10. **注意静态成员**：
    - 静态成员不属于对象，因此不参与继承。派生类可以访问基类的静态成员，但不能重新定义它们。
11. **避免过度耦合**：
    - 过度依赖继承可能会导致类之间的高度耦合，影响代码的可维护性和扩展性。
12. **文档和注释**：
    - 清晰地记录和注释你的继承关系和设计决策，以便其他开发者理解和维护代码。

以上是在C++中使用继承时需要注意的一些关键事项。遵循这些注意事项可以帮助你编写更清晰、更易于维护和扩展的代码。

### 1.4 什么情况下会发生对象切割？

对象切割（Object Slicing）在C++中发生在以下几种情况：

1. **赋值操作：**

- 当一个派生类对象被赋值给一个基类对象时，派生类对象的额外数据成员和成员函数（相对于基类的新特性）会被“切割”掉，只剩下基类的部分。

```c++
class Base {
public:
    int baseValue;
};

class Derived : public Base {
public:
    int derivedValue;
};

Derived d;
d.baseValue = 10;
d.derivedValue = 20;

Base b;
b = d; // 对象切割：b现在只包含基类部分，丢失了derivedValue
```

2. **函数参数按值传递：**

- 如果一个函数接受基类对象作为按值传递的参数，而你传递了一个派生类对象，那么在函数内部会发生对象切割。

```c++
void processBase(Base b) {
    // ...
}

Derived d;
processBase(d); // 对象切割：在processBase函数内部，b只包含基类部分
```

3. **容器中的元素存储：**

- 如果将派生类对象存储在保存基类元素的容器（如`std::vector<Base>`）中，也会发生对象切割。

```c++
std::vector<Base> baseVec;
Derived d;
baseVec.push_back(d); // 对象切割：在容器中，d的派生类部分被忽略
```

对象切割的发生主要是由于静态类型系统和对象的复制或赋值操作导致的。为了避免对象切割，通常建议使用指针或引用来处理多态性，或者考虑是否应该使用组合而不是继承。在需要存储不同类型对象的容器中，可以考虑使用指向对象的智能指针或其他间接访问机制。

### 1.5 如何避免对象切割？

1. **使用指针或引用：**

- 代替将派生类对象赋值给基类对象，使用基类指针或引用来操作派生类对象。

```c++
Base* basePtr = &d; // 使用指针
Base& baseRef = d; // 使用引用
```

使用指针`Base* basePtr = &d;`不会发生对象切割。这是因为指针只存储了对象的地址，而不复制对象本身。因此，通过指针，你可以访问派生类对象的所有成员，包括从基类继承的和在派生类中添加的新成员。

```c++
class Base {
public:
    int baseValue;
};

class Derived : public Base {
public:
    int derivedValue;
};

Derived d;
d.baseValue = 10;
d.derivedValue = 20;

Base* basePtr = &d;

std::cout << "Base value: " << basePtr->baseValue << std::endl; // 输出：Base value: 10
std::cout << "Derived value: " << static_cast<Derived*>(basePtr)->derivedValue << std::endl; // 输出：Derived value: 20
```

在这个例子中，通过`Base*`指针`basePtr`，我们能够访问派生类对象`d`的`baseValue`和`derivedValue`。请注意，为了访问`derivedValue`，我们需要使用`static_cast`将`basePtr`转换为`Derived*`。

总之，使用指针可以避免对象切割问题，并允许你保持对象的完整性和多态性。然而，使用指针时需要注意内存管理，以防止内存泄漏或悬挂指针等问题。在适当的情况下，也可以考虑使用智能指针来自动管理对象的生命周期。

2. **使用多态性：**

- 在基类中声明虚函数（使用`virtual`关键字），并在派生类中重写这些函数。这样，通过基类的指针或引用调用虚函数时，会根据实际对象的类型调用相应的函数。

```c++
class Base {
public:
    virtual void process() = 0; // 声明虚函数
};

class Derived : public Base {
public:
    void process() override { /* 实现 */ }
};
```

3. **使用容器存储指针或智能指针：**

- 如果需要在容器中存储不同类型的对象，使用指向对象的指针或智能指针（如`std::unique_ptr`或`std::shared_ptr`）。

```c++
std::vector<std::unique_ptr<Base>> baseVec;
Derived d;
baseVec.push_back(std::make_unique<Derived>(d)); // 存储派生类对象的智能指针
```

4. **重新考虑设计**：

- 如果发现频繁出现对象切割的问题，可能需要重新考虑你的设计。有时候，使用组合（has-a关系）而非继承（is-a关系）可能会更适合。

5. **避免按值传递派生类对象**：

- 如果函数需要处理不同类型的对象，尽量避免按值传递参数。改为使用指针或引用作为参数。

```c++
void processBase(Base* b) {
    // ...
}

processBase(&d); // 传递派生类对象的指针
```

通过以上方法，你可以避免对象切割问题，并保持对象的完整性和多态性。在设计和编写代码时，应始终考虑到潜在的对象切割风险，并选择合适的编程实践来避免它。

## 2. 继承方式

### 2.1 公有继承

**公有继承（Public Inheritance）**：

- 派生类公开继承基类的公共和保护成员。
- 派生类的对象可以被当作基类的对象来使用，这是多态的基础

```c++
class Base {
public:
    void publicFunc() {}
protected:
    void protectedFunc() {}
private:
    void privateFunc() {} // 不可访问
};

class Derived : public Base {
public:
    void derivedFunc() {}
};
```

### 2.2 私有继承

**私有继承（Private Inheritance）：**

- 派生类继承了基类的所有成员，但基类的公共和保护成员在派生类中变为私有成员。
- 派生类的对象不能被当作基类的对象来使用。

```c++
class Derived : private Base {
public:
    void derivedFunc() {}
};
```

**派生类的对象不能被当作基类的对象来使用是什么意思？**

- 在私有继承中，基类的公共和保护成员在派生类中变为私有成员。由于私有成员对外部代码（包括派生类的外部代码）不可见，所以不能直接通过派生类的对象访问这些原本在基类中是公共或保护的成员。因此，你不能将派生类的对象赋值给基类的引用或指针，也不能通过基类的引用来调用派生类对象的函数。
- 在受保护继承中，基类的公共成员在派生类中变为保护成员。虽然派生类的子类可以访问这些保护成员，但外部代码仍然不能直接通过派生类的对象访问它们。因此，同样不能将派生类的对象当作基类的对象来使用。

然而，对于公有继承，情况就不同了。在公有继承中，派生类的对象可以被当作基类的对象来使用。这意味着你可以将派生类的对象赋值给基类的引用或指针，并通过这些引用来调用派生类对象的函数。这是多态性的一个基础，使得你可以使用基类的接口来操作不同类型（即派生类）的对象。

### 2.3 受保护继承

**受保护继承（Protected Inheritance）：**

- 派生类继承了基类的所有成员，但基类的公共成员在派生类中变为保护成员。
- 派生类的对象不能被当作基类的对象来使用。

```c++
class Derived : protected Base {
public:
    void derivedFunc() {}
};
```

## 3. 多态

### 3.1 多态的条件

C++中实现多态需要满足以下条件：

1. **继承关系**：
   - 必须存在一个继承体系，即派生类从基类继承。
2. **虚函数**：
   - 基类中需要定义至少一个虚函数（virtual function）。虚函数使用关键字`virtual`声明，并在派生类中可以被重写（override）。
3. **动态绑定**：
   - 多态性通常与动态绑定（也称为延迟绑定或运行时绑定）相关联。这意味着函数调用的实际代码是在运行时确定的，而不是在编译时。
4. **父类指针或引用指向子类对象**：
   - 必须通过基类的指针或引用来访问派生类的对象。这样，当通过这些指针或引用调用虚函数时，会根据对象的实际类型调用相应的函数。

```c++
class Base {
public:
    virtual void display() {
        std::cout << "Base class" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() override {
        std::cout << "Derived class" << std::endl;
    }
};

int main() {
    Base* basePtr = new Derived(); // 创建一个Derived对象并将其赋值给Base指针
    basePtr->display(); // 输出："Derived class"

    delete basePtr; // 释放内存
    return 0;
}
```

在这个例子中，我们有一个基类`Base`和一个派生类`Derived`，`Base`类包含一个虚函数`display()`。在主函数中，我们创建了一个`Derived`对象并通过`Base`指针来访问它。当我们调用`display()`函数时，由于满足了多态的条件，实际执行的是`Derived`类中的重写版本，因此输出为"Derived class"。这就是C++中的多态性。

### 3.2 名词：动态绑定

动态绑定，也称为运行时绑定或延迟绑定，是面向对象编程中的一种机制。在C++中，动态绑定允许程序在运行时（而非编译时）确定要调用的函数版本。

当一个类包含虚函数（使用`virtual`关键字声明的函数），并且派生类重写了这个虚函数时，就可能发生动态绑定。在这种情况下，如果通过基类的指针或引用调用虚函数，那么实际执行的函数版本将根据指针或引用所指向的对象的实际类型来决定。

## 4. 其余知识

### 4.1 基类初始化

在派生类的构造函数初始化列表中，可以初始化基类的构造函数。

```c++
class Derived : public Base {
public:
    Derived(int value) : Base(value) {} // 初始化基类Base
};
```

### 4.2 继承和访问权限

+ 派生类可以访问基类的公共和保护成员。

- 派生类不能访问基类的私有成员。
- **派生类的外部代码只能访问派生类的公共成员和基类的公共/受保护成员。**

### 4.3 虚函数和多态

- 通过在基类中声明虚函数（使用`virtual`关键字），可以在派生类中重写该函数以实现运行时多态。
- 当通过基类指针或引用调用虚函数时，会根据实际对象的类型调用相应的函数。

```c++
class Base {
public:
    virtual void func() { std::cout << "Base" << std::endl; }
};

class Derived : public Base {
public:
    void func() override { std::cout << "Derived" << std::endl; }
};
```

通过继承，C++允许代码重用、层次化设计和多态性，使得程序更加灵活和模块化。然而，过度使用继承或者设计不当可能会导致复杂性和维护性问题，因此在设计类层次结构时需要谨慎考虑。

