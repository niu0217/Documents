# C++中类成员函数的this指针解析

代码：

```c++
//test.cpp

#include<iostream>
using namespace std;

class MYACLS {
public:
    int m_i;
    static int m_si; //声明
    int m_j;

    void myfunc() {
        m_i = 5;
        m_j = 6;
    }
};

int MYACLS::m_si = 10; //定义

int main()
{
    MYACLS myobj;
    MYACLS* pmyobj = new MYACLS();

    pmyobj->myfunc();

    return 0;
}
```

调试：

```bash
In file: /home/ubuntu/Dev/C++ObjectModern/data_semantics/test.cpp
   20 int main()
   21 {
   22     MYACLS myobj;
   23     MYACLS* pmyobj = new MYACLS();
   24
 ► 25     pmyobj->myfunc();
   26
   27     return 0;
   28 }
   
=> 0x00005555555551b0 <+39>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551b4 <+43>:	mov    rdi,rax
   0x00005555555551b7 <+46>:	call   0x55555555522a <MYACLS::myfunc()>
```

其中`rdi`寄存器中存的是类成员函数`MYACLS::myfunc()`的第一个参数，这也就是我们常说的this指针。它的值就是对象`pmyobj`的值。

我们来证明一下：

```bash
   0x5555555551b0 <main+39>                                                mov    rax, qword ptr [rbp - 0x10]
 ► 0x5555555551b4 <main+43>                                                mov    rdi, rax
 
 pwndbg> p pmyobj
$1 = (MYACLS *) 0x55555556aeb0
pwndbg> i r rax
rax            0x55555556aeb0      93824992325296
pwndbg>
```

我们看到寄存器`rax`保存的就是对象`pmyobj`的值，也就是我们常说的`this`指针。然后：

```bash
  0x5555555551b0 <main+39>                                                  mov    rax, qword ptr [rbp - 0x10]
  0x5555555551b4 <main+43>                                                  mov    rdi, rax
► 0x5555555551b7 <main+46>                                                  call   MYACLS::myfunc()                <MYACLS::myfunc()>
        rdi: 0x55555556aeb0 ◂— 0x0

pwndbg> i r rdi
rdi            0x55555556aeb0      93824992325296
pwndbg>
```

我们看到寄存器`rax`的值赋值给了`rdi`，也就是类成员函数`MYACLS::myfunc()`的第一个参数。

