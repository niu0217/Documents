# C++中虚表指针的初始化时机

## 分析

代码：

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Mon 05 Feb 2024 12:53:00 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

class MYACLS {
public:
    int m_i;
    int m_j;

    virtual void myvfunc() {

    }
    MYACLS() : m_i{0}, m_j{0} {

    }
    ~MYACLS() {
        int value = 0;
    }
};

int main()
{
    MYACLS aObj;
}
```

### 断点1

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]────────────────────────────────────────────────
In file: /home/ubuntu/Dev/C++ObjectModern/data_semantics/test.cpp
   24     }
   25 };
   26
   27 int main()
   28 {
 ► 29     MYACLS aObj;
   30 }

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rax rdi rsp 0x7fffffffe8e0 ◂— 0x0
01:0008│             0x7fffffffe8e8 —▸ 0x5555555550a0 (_start) ◂— endbr64
02:0010│             0x7fffffffe8f0 —▸ 0x7fffffffe9f0 ◂— 0x1
03:0018│             0x7fffffffe8f8 ◂— 0x7345deae9e110000
04:0020│ rbp         0x7fffffffe900 ◂— 0x0
05:0028│             0x7fffffffe908 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│             0x7fffffffe910 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│             0x7fffffffe918 —▸ 0x7fffffffe9f8 —▸ 0x7fffffffec60 ◂— '/home/ubuntu/Dev/C++ObjectModern/data_semantics/test'

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
   0x555555555195 <main+12>    mov    rax, qword ptr fs:[0x28]
   0x55555555519e <main+21>    mov    qword ptr [rbp - 8], rax
   0x5555555551a2 <main+25>    xor    eax, eax
   0x5555555551a4 <main+27>    lea    rax, [rbp - 0x20]
   0x5555555551a8 <main+31>    mov    rdi, rax
 ► 0x5555555551ab <main+34>    call   MYACLS::MYACLS()                <MYACLS::MYACLS()>
        rdi: 0x7fffffffe8e0 ◂— 0x0

   0x5555555551b0 <main+39>    lea    rax, [rbp - 0x20]
   0x5555555551b4 <main+43>    mov    rdi, rax
   0x5555555551b7 <main+46>    call   MYACLS::~MYACLS()                <MYACLS::~MYACLS()>

   0x5555555551bc <main+51>    mov    eax, 0
   0x5555555551c1 <main+56>    mov    rdx, qword ptr [rbp - 8]
```

分析：

```assembly
   # rax = rbp - 0x20 = 类对象aObj的地址 = 0x7fffffffe8e0
   0x5555555551a4 <main+27>    lea    rax, [rbp - 0x20] 
   
   # this指针 = rdi = rax = 类对象aObj的地址 = 0x7fffffffe8e0
   0x5555555551a8 <main+31>    mov    rdi, rax 
   
   
 ► 0x5555555551ab <main+34>    call   MYACLS::MYACLS()                <MYACLS::MYACLS()>
        rdi: 0x7fffffffe8e0 ◂— 0x0 # rdi中的值也被叫做this指针
```

```bash
# 类对象aObj的地址 = 0x7fffffffe8e0
pwndbg> p &aObj
$2 = (MYACLS *) 0x7fffffffe8e0

# rax = rbp - 0x20 = 类对象aObj的地址 = 0x7fffffffe8e0
pwndbg> i r rax
rax            0x7fffffffe8e0      140737488349408

# this指针 = rdi = rax = 类对象aObj的地址 = 0x7fffffffe8e0
pwndbg> i r rdi
rdi            0x7fffffffe8e0      140737488349408
```

因为类对象`aObj`是函数`main`中的局部变量，所以它是在栈中由编译器分配内存。

编译器将`rbp - 0x20`这块地址分配给了类对象`aObj`。

其中寄存器`rbp`保存的是函数`main`的调用栈的栈底指针。通过`[rbp - offset]`这样的方式可以取到在函数调用栈`main`中分配的所有局部变量的值。

然后将`rbp - 0x20`这个地址赋值给寄存器`rax`，此时寄存器`rax`里面保存的是类对象`aObj`的地址，也就是我们常说的`this`指针。

接着因为我们只是给类对象`aObj`分配了一个地址，但还没有给这个地址赋值，我们需要调用类的构造函数。我们知道，类的构造函数自带一个参数，就是this指针，它的值就是类对象`aObj`的地址。

### 断点2

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]────────────────────────────────────────────────
In file: /home/ubuntu/Dev/C++ObjectModern/data_semantics/test.cpp
   14     int m_j;
   15
   16     virtual void myvfunc() {
   17
   18     }
 ► 19     MYACLS() : m_i{0}, m_j{0} {
   20
   21     }
   22     ~MYACLS() {
   23         int value = 0;
   24     }

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rsp     0x7fffffffe8d8 —▸ 0x5555555551b0 (main+39) ◂— lea rax, [rbp - 0x20]
01:0008│ rax rdi 0x7fffffffe8e0 ◂— 0x0
02:0010│         0x7fffffffe8e8 —▸ 0x5555555550a0 (_start) ◂— endbr64
03:0018│         0x7fffffffe8f0 —▸ 0x7fffffffe9f0 ◂— 0x1
04:0020│         0x7fffffffe8f8 ◂— 0x7345deae9e110000
05:0028│ rbp     0x7fffffffe900 ◂— 0x0
06:0030│         0x7fffffffe908 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
07:0038│         0x7fffffffe910 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
 ► 0x55555555524e <MYACLS::MYACLS()>       endbr64
   0x555555555252 <MYACLS::MYACLS()+4>     push   rbp
   0x555555555253 <MYACLS::MYACLS()+5>     mov    rbp, rsp
   0x555555555256 <MYACLS::MYACLS()+8>     mov    qword ptr [rbp - 8], rdi
   0x55555555525a <MYACLS::MYACLS()+12>    lea    rdx, [rip + 0x2b27]           <vtable for MYACLS+16>
   0x555555555261 <MYACLS::MYACLS()+19>    mov    rax, qword ptr [rbp - 8]
   0x555555555265 <MYACLS::MYACLS()+23>    mov    qword ptr [rax], rdx
   0x555555555268 <MYACLS::MYACLS()+26>    mov    rax, qword ptr [rbp - 8]
   0x55555555526c <MYACLS::MYACLS()+30>    mov    dword ptr [rax + 8], 0
   0x555555555273 <MYACLS::MYACLS()+37>    mov    rax, qword ptr [rbp - 8]
   0x555555555277 <MYACLS::MYACLS()+41>    mov    dword ptr [rax + 0xc], 0
```

反汇编代码：

```assembly
pwndbg> disassemble
Dump of assembler code for function MYACLS::MYACLS():
=> 0x000055555555524e <+0>:	  endbr64
   0x0000555555555252 <+4>:	  push   rbp
   0x0000555555555253 <+5>:	  mov    rbp,rsp
   
   # rbp-0x8是编译器在MYACLS::MYACLS()的调用栈中分配的一个地址。
   # [rbp-0x8] = this指针 = rdi = 类对象aObj的地址 = 0x7fffffffe8e0
   # 后面我们都用this指针来代替rdi
   0x0000555555555256 <+8>:	  mov    QWORD PTR [rbp-0x8],rdi
   
   # rdx = 虚表指针的值 = 0x555555557d88
   0x000055555555525a <+12>:	lea    rdx,[rip+0x2b27]        # 0x555555557d88 <vtable for MYACLS+16>
   
   # rax = [rbp-0x8] = this指针 = 类对象aObj的地址 = 0x7fffffffe8e0
   0x0000555555555261 <+19>:	mov    rax,QWORD PTR [rbp-0x8]
   
   # rax + 0x0是虚表指针的地址
   # [rax] = [this指针] = [类对象aObj的地址] = [0x7fffffffe8e0] = 0x555555557d88
   0x0000555555555265 <+23>:	mov    QWORD PTR [rax],rdx
   
   # rax = [rbp-0x8] = this指针 = 类对象aObj的地址 = 0x7fffffffe8e0
   0x0000555555555268 <+26>:	mov    rax,QWORD PTR [rbp-0x8]
   
   # rax + 0x8是类成员变量m_i的地址
   # [rax + 0x8] = [this指针 + 0x8] = [类对象aObj的地址 + 0x8] = [0x7fffffffe8e0 + 0x8] = 0
   0x000055555555526c <+30>:	mov    DWORD PTR [rax+0x8],0x0
   
   # rax = [rbp-0x8] = this指针 = 类对象aObj的地址 = 0x7fffffffe8e0
   0x0000555555555273 <+37>:	mov    rax,QWORD PTR [rbp-0x8]
   
   # rax + 0xc是类成员变量m_j的地址
   # [rax + 0xc] = [this指针 + 0xc] = [类对象aObj的地址 + 0xc] = [0x7fffffffe8e0 + 0xc] = 0
   0x0000555555555277 <+41>:	mov    DWORD PTR [rax+0xc],0x0
   
   0x000055555555527e <+48>:	nop
   0x000055555555527f <+49>:	pop    rbp
   0x0000555555555280 <+50>:	ret
End of assembler dump.
```

### 断点3

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]────────────────────────────────────────────────
In file: /home/ubuntu/Dev/C++ObjectModern/data_semantics/test.cpp
   25 };
   26
   27 int main()
   28 {
   29     MYACLS aObj;
 ► 30 }

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rax rdi rsp 0x7fffffffe8e0 —▸ 0x555555557d88 (vtable for MYACLS+16) —▸ 0x55555555523e (MYACLS::myvfunc()) ◂— endbr64
01:0008│             0x7fffffffe8e8 ◂— 0x0
02:0010│             0x7fffffffe8f0 —▸ 0x7fffffffe9f0 ◂— 0x1
03:0018│             0x7fffffffe8f8 ◂— 0x7345deae9e110000
04:0020│ rbp         0x7fffffffe900 ◂— 0x0
05:0028│             0x7fffffffe908 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│             0x7fffffffe910 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│             0x7fffffffe918 —▸ 0x7fffffffe9f8 —▸ 0x7fffffffec60 ◂— '/home/ubuntu/Dev/C++ObjectModern/data_semantics/test'

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
   0x5555555551a8 <main+31>    mov    rdi, rax
   0x5555555551ab <main+34>    call   MYACLS::MYACLS()                <MYACLS::MYACLS()>

   0x5555555551b0 <main+39>    lea    rax, [rbp - 0x20]
   0x5555555551b4 <main+43>    mov    rdi, rax
   0x5555555551b7 <main+46>    call   MYACLS::~MYACLS()                <MYACLS::~MYACLS()>

 ► 0x5555555551bc <main+51>    mov    eax, 0
   0x5555555551c1 <main+56>    mov    rdx, qword ptr [rbp - 8]
   0x5555555551c5 <main+60>    xor    rdx, qword ptr fs:[0x28]
   0x5555555551ce <main+69>    je     main+76                <main+76>
    ↓
   0x5555555551d5 <main+76>    leave
   0x5555555551d6 <main+77>    ret
```

```bash
# 类对象aObj的地址
pwndbg> p &aObj
$1 = (MYACLS *) 0x7fffffffe8e0

# 类对象aObj的值的0～16字节
pwndbg> x/2gx 0x7fffffffe8e0
0x7fffffffe8e0:	0x0000555555557d88	0x0000000000000000

# 类对象aObj的值的0～8个字节。
# 0x0000555555557d88就是虚表指针的值
pwndbg> x/gx 0x7fffffffe8e0
0x7fffffffe8e0:	0x0000555555557d88

# 类对象aObj的值的8～12个字节。
# 0x00000000就是m_i的值
pwndbg> x/wx 0x7fffffffe8e8
0x7fffffffe8e8:	0x00000000

# 类对象aObj的值的12～16个字节。
# 0x00000000就是m_j的值
pwndbg> x/wx 0x7fffffffe8ec
0x7fffffffe8ec:	0x00000000
```

## 总结

+ 虚表指针，是在类的构造函数中进行初始化的。

+ 当创建一个类对象的时候，编译器自动的在类的构造函数中插入一些代码，用来初始化虚函数表指针。

  比如：

  ```c++
  MYACLS() : m_i{0}, m_j{0} {
  
  }
  ```

  这个构造函数中，我们什么代码也没写，但是，我们查看汇编代码时：

  ```assembly
  pwndbg> disassemble
  Dump of assembler code for function MYACLS::MYACLS():
  => 0x000055555555524e <+0>:	  endbr64
     0x0000555555555252 <+4>:	  push   rbp
     0x0000555555555253 <+5>:	  mov    rbp,rsp
     0x0000555555555256 <+8>:	  mov    QWORD PTR [rbp-0x8],rdi
     0x000055555555525a <+12>:	lea    rdx,[rip+0x2b27]        # 0x555555557d88 <vtable for MYACLS+16>
     0x0000555555555261 <+19>:	mov    rax,QWORD PTR [rbp-0x8]
     0x0000555555555265 <+23>:	mov    QWORD PTR [rax],rdx
     0x0000555555555268 <+26>:	mov    rax,QWORD PTR [rbp-0x8]
     0x000055555555526c <+30>:	mov    DWORD PTR [rax+0x8],0x0
     0x0000555555555273 <+37>:	mov    rax,QWORD PTR [rbp-0x8]
     0x0000555555555277 <+41>:	mov    DWORD PTR [rax+0xc],0x0
     0x000055555555527e <+48>:	nop
     0x000055555555527f <+49>:	pop    rbp
     0x0000555555555280 <+50>:	ret
  End of assembler dump.
  ```

  我们发现编译器在这里悄悄的给虚表指针赋了值。

+ 虚表指针位于一个类对象内存布局的开始。这个和编译器的设计有关。

  ```bash
  # 类对象aObj的地址
  pwndbg> p &aObj
  $1 = (MYACLS *) 0x7fffffffe8e0
  
  # 类对象aObj的值的0～16字节
  pwndbg> x/2gx 0x7fffffffe8e0
  0x7fffffffe8e0:	0x0000555555557d88	0x0000000000000000
  
  # 类对象aObj的值的0～8个字节。
  # 0x0000555555557d88就是虚表指针的值
  pwndbg> x/gx 0x7fffffffe8e0
  0x7fffffffe8e0:	0x0000555555557d88
  
  # 类对象aObj的值的8～12个字节。
  # 0x00000000就是m_i的值
  pwndbg> x/wx 0x7fffffffe8e8
  0x7fffffffe8e8:	0x00000000
  
  # 类对象aObj的值的12～16个字节。
  # 0x00000000就是m_j的值
  pwndbg> x/wx 0x7fffffffe8ec
  0x7fffffffe8ec:	0x00000000
  ```

  在这里看到类对象`aObj`的0～8字节保存的是虚表指针`0x0000555555557d88`，然后才是类成员变量。

