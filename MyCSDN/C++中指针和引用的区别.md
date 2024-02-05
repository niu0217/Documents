# C++中指针和引用的区别

## GPT的回答

C++ 中指针和引用都是用于间接访问其他变量的方式，但它们在语法和使用上有明显的区别。

主要区别如下：

1. 语法不同：
   - 指针：使用操作符 `*` 来定义，`->` 来访问成员。
   - 引用：使用 `&` 定义，访问方式与普通变量相同。
2. null 值：
   - 指针：可以指向 `nullptr` 或者无效地址。
   - 引用：在定义时必须被初始化，且不可能引用到 `nullptr`。
3. 重新赋值：
   - 指针：可以改变指向，指向另外的变量。
   - 引用：一旦初始化后，就不能改变引用的目标。
4. 内存占用：
   - 指针：占用单独的内存地址。
   - 引用：通常不占用内存地址，但这取决于编译器的实现。
5. 间接访问：
   - 指针：需要显示地使用解引用操作符（`*`）来访问目标变量的值。
   - 引用：直接操作，就如同操作普通变量一样。

## 从汇编的角度来分析

### 指针

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Sun 04 Feb 2024 08:12:19 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
    int a = 9;
    int* pValue = &a;

    *pValue = 20;

    return 0;
}
```

反汇编代码：

```assembly
pwndbg> disassemble
Dump of assembler code for function main():
   0x0000555555555189 <+0>:	endbr64
   0x000055555555518d <+4>:	push   rbp
   0x000055555555518e <+5>:	mov    rbp,rsp
   0x0000555555555191 <+8>:	sub    rsp,0x20
   0x0000555555555195 <+12>:	mov    rax,QWORD PTR fs:0x28
   0x000055555555519e <+21>:	mov    QWORD PTR [rbp-0x8],rax
   0x00005555555551a2 <+25>:	xor    eax,eax
=> 0x00005555555551a4 <+27>:	mov    DWORD PTR [rbp-0x14],0x9
   0x00005555555551ab <+34>:	lea    rax,[rbp-0x14]
   0x00005555555551af <+38>:	mov    QWORD PTR [rbp-0x10],rax
   0x00005555555551b3 <+42>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551b7 <+46>:	mov    DWORD PTR [rax],0x14
   0x00005555555551bd <+52>:	mov    eax,0x0
   0x00005555555551c2 <+57>:	mov    rdx,QWORD PTR [rbp-0x8]
   0x00005555555551c6 <+61>:	xor    rdx,QWORD PTR fs:0x28
   0x00005555555551cf <+70>:	je     0x5555555551d6 <main()+77>
   0x00005555555551d1 <+72>:	call   0x555555555080 <__stack_chk_fail@plt>
   0x00005555555551d6 <+77>:	leave
   0x00005555555551d7 <+78>:	ret
End of assembler dump.
```

我们开始逐步分析：

（1）我们让断点停在`int a = 9;`这一行；

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]──────────────────────────────────────────────
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
    8 #include<iostream>
    9 using namespace std;
   10
   11 int main()
   12 {
 ► 13     int a = 9;
   14     int* pValue = &a;
   15
   16     *pValue = 20;
   17
   18     return 0;

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rsp 0x7fffffffe930 ◂— 0x0
01:0008│     0x7fffffffe938 —▸ 0x5555555550a0 (_start) ◂— endbr64
02:0010│     0x7fffffffe940 —▸ 0x7fffffffea40 ◂— 0x1
03:0018│     0x7fffffffe948 ◂— 0x38e5b8a291d89000
04:0020│ rbp 0x7fffffffe950 ◂— 0x0
05:0028│     0x7fffffffe958 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│     0x7fffffffe960 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│     0x7fffffffe968 —▸ 0x7fffffffea48 —▸ 0x7fffffffecb8 ◂— '/home/ubuntu/Dev/MyCSDN/test'

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
   0x55555555518e <main+5>     mov    rbp, rsp
   0x555555555191 <main+8>     sub    rsp, 0x20
   0x555555555195 <main+12>    mov    rax, qword ptr fs:[0x28]
   0x55555555519e <main+21>    mov    qword ptr [rbp - 8], rax
   0x5555555551a2 <main+25>    xor    eax, eax
 ► 0x5555555551a4 <main+27>    mov    dword ptr [rbp - 0x14], 9
   0x5555555551ab <main+34>    lea    rax, [rbp - 0x14]
   0x5555555551af <main+38>    mov    qword ptr [rbp - 0x10], rax
   0x5555555551b3 <main+42>    mov    rax, qword ptr [rbp - 0x10]
   0x5555555551b7 <main+46>    mov    dword ptr [rax], 0x14
   0x5555555551bd <main+52>    mov    eax, 0
```

函数main的调用栈：

```assembly
────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rsp 0x7fffffffe930 ◂— 0x0
01:0008│     0x7fffffffe938 —▸ 0x5555555550a0 (_start) ◂— endbr64
02:0010│     0x7fffffffe940 —▸ 0x7fffffffea40 ◂— 0x1
03:0018│     0x7fffffffe948 ◂— 0x38e5b8a291d89000
04:0020│ rbp 0x7fffffffe950 ◂— 0x0
05:0028│     0x7fffffffe958 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│     0x7fffffffe960 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│     0x7fffffffe968 —▸ 0x7fffffffea48 —▸ 0x7fffffffecb8 ◂— '/home/ubuntu/Dev/MyCSDN/test'
```

+ 寄存器`rbp`：栈基指针，指向栈的底部，可以通过`[rbp - offset]`取得保存在栈中的数据；
+ 寄存器`rsp`：栈顶指针，指向栈的顶部；

（2）执行`int a = 9;`

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]────────────────────────────────────────────────
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
    9 using namespace std;
   10
   11 int main()
   12 {
   13     int a = 9;
 ► 14     int* pValue = &a;
   15
   16     *pValue = 20;
   17
   18     return 0;
   19 }

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rsp 0x7fffffffe930 ◂— 0x0
01:0008│     0x7fffffffe938 ◂— 0x9555550a0
02:0010│     0x7fffffffe940 —▸ 0x7fffffffea40 ◂— 0x1
03:0018│     0x7fffffffe948 ◂— 0x38e5b8a291d89000
04:0020│ rbp 0x7fffffffe950 ◂— 0x0
05:0028│     0x7fffffffe958 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│     0x7fffffffe960 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│     0x7fffffffe968 —▸ 0x7fffffffea48 —▸ 0x7fffffffecb8 ◂— '/home/ubuntu/Dev/MyCSDN/test'

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
   0x555555555191 <main+8>     sub    rsp, 0x20
   0x555555555195 <main+12>    mov    rax, qword ptr fs:[0x28]
   0x55555555519e <main+21>    mov    qword ptr [rbp - 8], rax
   0x5555555551a2 <main+25>    xor    eax, eax
   0x5555555551a4 <main+27>    mov    dword ptr [rbp - 0x14], 9
 ► 0x5555555551ab <main+34>    lea    rax, [rbp - 0x14]
   0x5555555551af <main+38>    mov    qword ptr [rbp - 0x10], rax
   0x5555555551b3 <main+42>    mov    rax, qword ptr [rbp - 0x10]
   0x5555555551b7 <main+46>    mov    dword ptr [rax], 0x14
   0x5555555551bd <main+52>    mov    eax, 0
   0x5555555551c2 <main+57>    mov    rdx, qword ptr [rbp - 8]
```

```bash
pwndbg> p &a
$3 = (int *) 0x7fffffffe93c

pwndbg> x/wx 0x7fffffffe93c
0x7fffffffe93c:	0x00000009

pwndbg> x/wx $rbp - 0x14
0x7fffffffe93c:	0x00000009
```

因为变量`a`是函数`main`中的局部变量，所以编译器会给变量`a`在函数`main`的调用栈中分配内存；

编译器给变量`a`分配的栈地址为`0x7fffffffe93c`，然后通过`rbp - 0x14`来取得变量a的地址，通过`dword ptr [rbp - 0x14]`来取得变量a的值；

解释一下：变量`a`是int型的，占四个字节，`dword ptr`表示的就是取4个字节。

总结一下我们在这一步得到的信息：

+ 变量`a`的地址：`rbp - 0x14`
+ 变量`a`的值：`[rbp - 0x14]`

（3）执行`int* pValue = &a;`

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]────────────────────────────────────────────────
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
   11 int main()
   12 {
   13     int a = 9;
   14     int* pValue = &a;
   15
 ► 16     *pValue = 20;
   17
   18     return 0;
   19 }

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rsp   0x7fffffffe930 ◂— 0x0
01:0008│ rax-4 0x7fffffffe938 ◂— 0x9555550a0
02:0010│       0x7fffffffe940 —▸ 0x7fffffffe93c ◂— 0xffffe93c00000009 /* '\t' */
03:0018│       0x7fffffffe948 ◂— 0x38e5b8a291d89000
04:0020│ rbp   0x7fffffffe950 ◂— 0x0
05:0028│       0x7fffffffe958 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│       0x7fffffffe960 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│       0x7fffffffe968 —▸ 0x7fffffffea48 —▸ 0x7fffffffecb8 ◂— '/home/ubuntu/Dev/MyCSDN/test'

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
   0x55555555519e <main+21>    mov    qword ptr [rbp - 8], rax
   0x5555555551a2 <main+25>    xor    eax, eax
   0x5555555551a4 <main+27>    mov    dword ptr [rbp - 0x14], 9
   0x5555555551ab <main+34>    lea    rax, [rbp - 0x14]
   0x5555555551af <main+38>    mov    qword ptr [rbp - 0x10], rax
 ► 0x5555555551b3 <main+42>    mov    rax, qword ptr [rbp - 0x10]
   0x5555555551b7 <main+46>    mov    dword ptr [rax], 0x14
   0x5555555551bd <main+52>    mov    eax, 0
   0x5555555551c2 <main+57>    mov    rdx, qword ptr [rbp - 8]
   0x5555555551c6 <main+61>    xor    rdx, qword ptr fs:[0x28]
   0x5555555551cf <main+70>    je     main+77                <main+77>
```

编译器给指针变量`pValue`在`main`函数的调用栈中分配了一个栈地址`rbp - 0x10`，其中`[rbp - 0x10]`的值是随机的；

然后，将`rbp - 0x14`赋值给寄存器`rax`，也就是此时寄存器`rax`保存的是变量`a`的地址；

最后我们把`rax`的值赋值给`[rbp - 0x10]`。此时变量`pValue`的值就是变量`a`的地址，这就是指针变量`pValue`的作用，它的值保存的是一个地址；

总结一下：

+ 指针变量`pValue`的地址：`rbp - 0x10`
+ 指针变量`pValue`的值：`rbp - 0x14`，也就是a的地址

（4）执行`*pValue = 20;`

```assembly
────────────────────────────────────────────────────────[ SOURCE (CODE) ]────────────────────────────────────────────────
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
   13     int a = 9;
   14     int* pValue = &a;
   15
   16     *pValue = 20;
   17
 ► 18     return 0;
   19 }

────────────────────────────────────────────────────────────[ STACK ]────────────────────────────────────────────────────
00:0000│ rsp   0x7fffffffe930 ◂— 0x0
01:0008│ rax-4 0x7fffffffe938 ◂— 0x14555550a0
02:0010│       0x7fffffffe940 —▸ 0x7fffffffe93c ◂— 0xffffe93c00000014
03:0018│       0x7fffffffe948 ◂— 0x38e5b8a291d89000
04:0020│ rbp   0x7fffffffe950 ◂— 0x0
05:0028│       0x7fffffffe958 —▸ 0x7ffff7c07083 (__libc_start_main+243) ◂— mov edi, eax
06:0030│       0x7fffffffe960 —▸ 0x7ffff7dcfb80 (main_arena) ◂— 0x0
07:0038│       0x7fffffffe968 —▸ 0x7fffffffea48 —▸ 0x7fffffffecb8 ◂— '/home/ubuntu/Dev/MyCSDN/test'

───────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────
   0x5555555551a4 <main+27>    mov    dword ptr [rbp - 0x14], 9
   0x5555555551ab <main+34>    lea    rax, [rbp - 0x14]
   0x5555555551af <main+38>    mov    qword ptr [rbp - 0x10], rax
   0x5555555551b3 <main+42>    mov    rax, qword ptr [rbp - 0x10]
   0x5555555551b7 <main+46>    mov    dword ptr [rax], 0x14
 ► 0x5555555551bd <main+52>    mov    eax, 0
   0x5555555551c2 <main+57>    mov    rdx, qword ptr [rbp - 8]
   0x5555555551c6 <main+61>    xor    rdx, qword ptr fs:[0x28]
   0x5555555551cf <main+70>    je     main+77                <main+77>
    ↓
   0x5555555551d6 <main+77>    leave
   0x5555555551d7 <main+78>    ret
```

首先，将`[rbp - 0x10]`赋值给寄存器`rax`，也就是将变量`pValue`的值，赋值给寄存器`rax`，此时寄存器`rax`的值就是变量`a`的地址；

然后，将0x14，转换成10进制就是20，赋值给`[rax]`，而`rax`保存的是`a`的地址，即：此时`a`的值就是20了；

总结一下：

+ 先将`pValue`的值保存在寄存器`rax`中；
+ 然后使用`[rax]`，间接寻址的方式，将`rax`的值解释为一个地址，取这个地址的值。也就是`*pValue`；

### 引用

代码：

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Sun 04 Feb 2024 08:12:19 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
    int a = 9;
    int& pValue = a;

    pValue = 20;

    return 0;
}
```

反汇编代码：

```assembly
pwndbg> disassemble
Dump of assembler code for function main():
   0x0000555555555189 <+0>:	endbr64
   0x000055555555518d <+4>:	push   rbp
   0x000055555555518e <+5>:	mov    rbp,rsp
   0x0000555555555191 <+8>:	sub    rsp,0x20
   0x0000555555555195 <+12>:	mov    rax,QWORD PTR fs:0x28
   0x000055555555519e <+21>:	mov    QWORD PTR [rbp-0x8],rax
   0x00005555555551a2 <+25>:	xor    eax,eax
=> 0x00005555555551a4 <+27>:	mov    DWORD PTR [rbp-0x14],0x9
   0x00005555555551ab <+34>:	lea    rax,[rbp-0x14]
   0x00005555555551af <+38>:	mov    QWORD PTR [rbp-0x10],rax
   0x00005555555551b3 <+42>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551b7 <+46>:	mov    DWORD PTR [rax],0x14
   0x00005555555551bd <+52>:	mov    eax,0x0
   0x00005555555551c2 <+57>:	mov    rdx,QWORD PTR [rbp-0x8]
   0x00005555555551c6 <+61>:	xor    rdx,QWORD PTR fs:0x28
   0x00005555555551cf <+70>:	je     0x5555555551d6 <main()+77>
   0x00005555555551d1 <+72>:	call   0x555555555080 <__stack_chk_fail@plt>
   0x00005555555551d6 <+77>:	leave
   0x00005555555551d7 <+78>:	ret
End of assembler dump.
```

其中：

```assembly
   # int a = 9;
=> 0x00005555555551a4 <+27>:	mov    DWORD PTR [rbp-0x14],0x9

   # int& pValue = a;
   0x00005555555551ab <+34>:	lea    rax,[rbp-0x14]
   0x00005555555551af <+38>:	mov    QWORD PTR [rbp-0x10],rax
   
   # pValue = 20;
   0x00005555555551b3 <+42>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551b7 <+46>:	mov    DWORD PTR [rax],0x14
```

对比指针的做法：

```assembly
   # int a = 9;
=> 0x00005555555551a4 <+27>:	mov    DWORD PTR [rbp-0x14],0x9

   # int* pValue = &a;
   0x00005555555551ab <+34>:	lea    rax,[rbp-0x14]
   0x00005555555551af <+38>:	mov    QWORD PTR [rbp-0x10],rax
   
   # *pValue = 20;
   0x00005555555551b3 <+42>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551b7 <+46>:	mov    DWORD PTR [rax],0x14
```

我们看到，在汇编代码层次，引用和指针存取值的方法一模一样。

那为什么指针和引用的用法会不同呢？

+ 我认为是编译器在其中做文章。
+ 大家有什么看法，欢迎留言。