# new和delete

## 1. malloc来分配0个字节

很糟糕的做法！！！！！！！！

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Thu 08 Feb 2024 04:50:35 PM CST
> Description:
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

void func() {
    void* p = malloc(0);
    // char* p = new char[0];

    int value;
    value = 1;
}

int main()
{
    func();
}
```

`p`中的内容修改必出错！！！！！

## 2. new内存分配细节分析

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Thu 08 Feb 2024 04:50:35 PM CST
> Description:
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

void func() {
    char* ppoint = new char[10];
    memset(ppoint, 0, 10);
    delete []ppoint;
}

int main()
{
    func();
}
```

一块内存的回收，影响范围很广，远远不是10字节，而是一大片。

## 3. 重载类中的operator new/delete

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Thu 08 Feb 2024 04:50:35 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    static void* operator new(size_t size);
    static void operator delete(void* phead);
public:
    A() {
        cout<<"A::A()\n";
    }
    ~A() {
        cout<<"A::~A()\n";
    }
};

void* A::operator new(size_t size) {
    A* ppoint = (A*)malloc(size);
    return ppoint;
}

void A::operator delete(void* phead) {
    free(phead);
}

void func() {
  	//先调用我们自己的operator new，然后调用A的构造函数
    A* pa = new A();
    //先调用A的析构函数，然后调用我们自己的operator delete
    delete pa;
}

void func2() {
    //调用编译器的operator new和operator delete
    A* pa = ::new A();
    ::delete pa;
}

int main()
{
    func();
    func2();
}
```

## 4. 重载类中的operator new[]/delete[]

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Thu 08 Feb 2024 04:50:35 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    static void* operator new[](size_t size);
    static void operator delete[](void* phead);
public:
    A() {
        cout<<"A::A()\n";
    }
    ~A() {
        cout<<"A::~A()\n";
    }
};

void* A::operator new[](size_t size) {
    A* ppoint = (A*)malloc(size);
    return ppoint;
}

void A::operator delete[](void* phead) {
    free(phead);
}

void func() {
    //构造和析构函数被调用3次，
    //但是operator new[]和operator delete[]只被调用一次
    A* pa = new A[3];
    delete []pa;
}

int main()
{
    func();
}
```

调试：

```c++
In file: /home/ubuntu/Dev/C++ObjectModern/constructor/test.cpp
   21     }
   22 };
   23
   24 void* A::operator new[](size_t size) {
   25     A* ppoint = (A*)malloc(size);
 ► 26     return ppoint;
   27 }
   28
   29 void A::operator delete[](void* phead) {
   30     free(phead);
   31 }

pwndbg> p ppoint
$7 = (A *) 0x55555556aeb0
pwndbg> x/3gx 0x55555556aeb0
0x55555556aeb0:	0x0000000000000000	0x0000000000000000
0x55555556aec0:	0x0000000000000000
```

```c++
In file: /home/ubuntu/Dev/C++ObjectModern/constructor/test.cpp
   32
   33 void func() {
   34     //构造和析构函数被调用3次，
   35     //但是operator new[]和operator delete[]只被调用一次
   36     A* pa = new A[3];
 ► 37     delete []pa;
   38 }
   39
   40 int main()
   41 {
   42     func();
     
pwndbg> p pa
$8 = (A *) 0x55555556aeb8
pwndbg> x/3gx 0x55555556aeb0
0x55555556aeb0:	0x0000000000000003	0x0000000000000000
0x55555556aec0:	0x0000000000000000
```

从这里我们看到`operator new[]`申请的是`0x55555556aeb0`，但是返回的却是`0x55555556aeb8`，相差了8个字节，这8个字节用来记录大小`0x55555556aeb0:	0x0000000000000003`



