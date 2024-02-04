# C++中函数参数如何传递给函数

## 情况一

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Sun 04 Feb 2024 08:12:19 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

int myfunc(int a, int b, int c, int d, int e, int f) {
    a = 10;
    b = 20;
    c = 30;
    d = 40;
    e = 50;
    f = 60;
    return 100;
}

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    myfunc(a, b, c, d, e, f);
    return 0;
}
```

调试：

```bash
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
   24     int b = 0;
   25     int c = 0;
   26     int d = 0;
   27     int e = 0;
   28     int f = 0;
 ► 29     myfunc(a, b, c, d, e, f);
   30     return 0;
   31 }

pwndbg> disassemble
Dump of assembler code for function main():
   0x00005555555551b6 <+0>:	endbr64
   0x00005555555551ba <+4>:	push   rbp
   0x00005555555551bb <+5>:	mov    rbp,rsp
   0x00005555555551be <+8>:	sub    rsp,0x20
   0x00005555555551c2 <+12>:	mov    DWORD PTR [rbp-0x18],0x0 #a
   0x00005555555551c9 <+19>:	mov    DWORD PTR [rbp-0x14],0x0 #b
   0x00005555555551d0 <+26>:	mov    DWORD PTR [rbp-0x10],0x0 #c
   0x00005555555551d7 <+33>:	mov    DWORD PTR [rbp-0xc],0x0  #d
   0x00005555555551de <+40>:	mov    DWORD PTR [rbp-0x8],0x0  #e
   0x00005555555551e5 <+47>:	mov    DWORD PTR [rbp-0x4],0x0  #f
=> 0x00005555555551ec <+54>:	mov    r8d,DWORD PTR [rbp-0x4]
   0x00005555555551f0 <+58>:	mov    edi,DWORD PTR [rbp-0x8]
   0x00005555555551f3 <+61>:	mov    ecx,DWORD PTR [rbp-0xc]
   0x00005555555551f6 <+64>:	mov    edx,DWORD PTR [rbp-0x10]
   0x00005555555551f9 <+67>:	mov    esi,DWORD PTR [rbp-0x14]
   0x00005555555551fc <+70>:	mov    eax,DWORD PTR [rbp-0x18]
   0x00005555555551ff <+73>:	mov    r9d,r8d
   0x0000555555555202 <+76>:	mov    r8d,edi
   0x0000555555555205 <+79>:	mov    edi,eax
   0x0000555555555207 <+81>:	call   0x555555555169 <myfunc(int, int, int, int, int, int)>
   0x000055555555520c <+86>:	mov    eax,0x0
   0x0000555555555211 <+91>:	leave
   0x0000555555555212 <+92>:	ret
End of assembler dump.
```

分析下面汇编代码：

```assembly
 0x00005555555551c2 <+12>:	mov    DWORD PTR [rbp-0x18],0x0 #a
 0x00005555555551c9 <+19>:	mov    DWORD PTR [rbp-0x14],0x0 #b
 0x00005555555551d0 <+26>:	mov    DWORD PTR [rbp-0x10],0x0 #c
 0x00005555555551d7 <+33>:	mov    DWORD PTR [rbp-0xc],0x0  #d
 0x00005555555551de <+40>:	mov    DWORD PTR [rbp-0x8],0x0  #e
 0x00005555555551e5 <+47>:	mov    DWORD PTR [rbp-0x4],0x0  #f
```

我们清楚的看到变量a、b、c、d、e、f是保存在内存中的。

接着继续分析:

```bash
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
   24     int b = 0;
   25     int c = 0;
   26     int d = 0;
   27     int e = 0;
   28     int f = 0;
 ► 29     myfunc(a, b, c, d, e, f);
   30     return 0;
   31 }

─────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────────
   0x5555555551f9 <main+67>                                                  mov    esi, dword ptr [rbp - 0x14]
   0x5555555551fc <main+70>                                                  mov    eax, dword ptr [rbp - 0x18]
   0x5555555551ff <main+73>                                                  mov    r9d, r8d
   0x555555555202 <main+76>                                                  mov    r8d, edi
   0x555555555205 <main+79>                                                  mov    edi, eax
 ► 0x555555555207 <main+81>                                                  call   myfunc(int, int, int, int, int, int)                <myfunc(int, int, int, int, int, int)>
        rdi: 0x0
        rsi: 0x0
        rdx: 0x0
        rcx: 0x0
        r8: 0x0
        r9: 0x0
```

我们看到变量a、b、c、d、e、f的值分别赋值给了寄存器：

```ass
rdi: 0x0
rsi: 0x0
rdx: 0x0
rcx: 0x0
r8: 0x0
r9: 0x0
```

即：通过寄存器，将参数传递给了函数myfunc。

补充知识：

+ `rdi`：函数调用时通常用来保存函数的第1个参数；
+ `rsi`：函数调用时通常用来保存函数的第2个参数；
+ `rdx`：函数调用时通常用来保存函数的第3个参数；
+ `rcx`：函数调用时通常用来保存函数的第4个参数；
+ `r8`：函数调用时通常用来保存函数的第5个参数；
+ `r9`：函数调用时通常用来保存函数的第6个参数；

## 情况二

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Sun 04 Feb 2024 08:12:19 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

int myfunc(int a, int b, int c, int d, int e, int f,
           int g, int h, int i) {
    a = 10;
    b = 20;
    c = 30;
    d = 40;
    e = 50;
    f = 60;
    g = 70;
    h = 80;
    i = 90;
    return 100;
}

int main()
{
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    int g = 6;
    int h = 7;
    int i = 8;
    myfunc(a, b, c, d, e, f, g, h, i);
    return 0;
}
```

调试：

```bash
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
   31     int e = 4;
   32     int f = 5;
   33     int g = 6;
   34     int h = 7;
   35     int i = 8;
 ► 36     myfunc(a, b, c, d, e, f, g, h, i);
   37     return 0;
   38 }
   
Dump of assembler code for function main():
   0x00005555555551cb <+0>:	endbr64
   0x00005555555551cf <+4>:	push   rbp
   0x00005555555551d0 <+5>:	mov    rbp,rsp
   0x00005555555551d3 <+8>:	sub    rsp,0x30
   0x00005555555551d7 <+12>:	mov    DWORD PTR [rbp-0x24],0x0 #a
   0x00005555555551de <+19>:	mov    DWORD PTR [rbp-0x20],0x1 #b
   0x00005555555551e5 <+26>:	mov    DWORD PTR [rbp-0x1c],0x2 #c
   0x00005555555551ec <+33>:	mov    DWORD PTR [rbp-0x18],0x3 #d
   0x00005555555551f3 <+40>:	mov    DWORD PTR [rbp-0x14],0x4 #e
   0x00005555555551fa <+47>:	mov    DWORD PTR [rbp-0x10],0x5 #f
   0x0000555555555201 <+54>:	mov    DWORD PTR [rbp-0xc],0x6  #g
   0x0000555555555208 <+61>:	mov    DWORD PTR [rbp-0x8],0x7  #h
   0x000055555555520f <+68>:	mov    DWORD PTR [rbp-0x4],0x8  #i
=> 0x0000555555555216 <+75>:	mov    r9d,DWORD PTR [rbp-0x10]
   0x000055555555521a <+79>:	mov    r8d,DWORD PTR [rbp-0x14]
   0x000055555555521e <+83>:	mov    ecx,DWORD PTR [rbp-0x18]
   0x0000555555555221 <+86>:	mov    edx,DWORD PTR [rbp-0x1c]
   0x0000555555555224 <+89>:	mov    esi,DWORD PTR [rbp-0x20]
   0x0000555555555227 <+92>:	mov    eax,DWORD PTR [rbp-0x24]
   0x000055555555522a <+95>:	mov    edi,DWORD PTR [rbp-0x4]
   0x000055555555522d <+98>:	push   rdi
   0x000055555555522e <+99>:	mov    edi,DWORD PTR [rbp-0x8]
   0x0000555555555231 <+102>:	push   rdi
   0x0000555555555232 <+103>:	mov    edi,DWORD PTR [rbp-0xc]
   0x0000555555555235 <+106>:	push   rdi
   0x0000555555555236 <+107>:	mov    edi,eax
   0x0000555555555238 <+109>:	call   0x555555555169 <myfunc(int, int, int, int, int, int, int, int, int)>
   0x000055555555523d <+114>:	add    rsp,0x18
   0x0000555555555241 <+118>:	mov    eax,0x0
   0x0000555555555246 <+123>:	leave
   0x0000555555555247 <+124>:	ret
End of assembler dump.
```

从：

```assembly
0x00005555555551d7 <+12>:	mov    DWORD PTR [rbp-0x24],0x0 #a
0x00005555555551de <+19>:	mov    DWORD PTR [rbp-0x20],0x1 #b
0x00005555555551e5 <+26>:	mov    DWORD PTR [rbp-0x1c],0x2 #c
0x00005555555551ec <+33>:	mov    DWORD PTR [rbp-0x18],0x3 #d
0x00005555555551f3 <+40>:	mov    DWORD PTR [rbp-0x14],0x4 #e
0x00005555555551fa <+47>:	mov    DWORD PTR [rbp-0x10],0x5 #f
0x0000555555555201 <+54>:	mov    DWORD PTR [rbp-0xc],0x6  #g
0x0000555555555208 <+61>:	mov    DWORD PTR [rbp-0x8],0x7  #h
0x000055555555520f <+68>:	mov    DWORD PTR [rbp-0x4],0x8  #i
```

我们看到变量的值是保存在内存中的，位于栈区。

继续分析：

```bash
In file: /home/ubuntu/Dev/MyCSDN/test.cpp
   31     int e = 4;
   32     int f = 5;
   33     int g = 6;
   34     int h = 7;
   35     int i = 8;
 ► 36     myfunc(a, b, c, d, e, f, g, h, i);
   37     return 0;
   38 }
   
─────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]──────────────────────────────────────────
   0x55555555522e <main+99>                                                mov    edi, dword ptr [rbp - 8]
   0x555555555231 <main+102>                                               push   rdi
   0x555555555232 <main+103>                                               mov    edi, dword ptr [rbp - 0xc]
   0x555555555235 <main+106>                                               push   rdi
   0x555555555236 <main+107>                                               mov    edi, eax
 ► 0x555555555238 <main+109>                                               call   myfunc(int, int, int, int, int, int, int, int, int)                <myfunc(int, int, int, int, int, int, int, int, int)>
        rdi: 0x0
        rsi: 0x1
        rdx: 0x2
        rcx: 0x3
        r8: 0x4
        r9: 0x5
        arg[6]: 0x6
        arg[7]: 0x7
        arg[8]: 0x8
```

我们看到：

```bash
rdi: 0x0 #a
rsi: 0x1 #b
rdx: 0x2 #c
rcx: 0x3 #d
r8: 0x4  #e
r9: 0x5  #f
```

这个情况一一样的情况，变量a、b、c、d、e、f通过寄存器传给函数myfunc。那为什么还多了：

```bash
arg[6]: 0x6 #g
arg[7]: 0x7 #h
arg[8]: 0x8 #i
```

原因：

+ 只有6个寄存器会用来保存函数的参数。
+ 如果参数大于6个，那么就会借助栈来保存多余的参数。

证明：

```assembly
0x0000555555555201 <+54>:	mov    DWORD PTR [rbp-0xc],0x6  #g
0x0000555555555208 <+61>:	mov    DWORD PTR [rbp-0x8],0x7  #h
0x000055555555520f <+68>:	mov    DWORD PTR [rbp-0x4],0x8  #i

0x000055555555522a <+95>:	  mov    edi,DWORD PTR [rbp-0x4] #i
0x000055555555522d <+98>:	  push   rdi #将i保存到栈中
0x000055555555522e <+99>:	  mov    edi,DWORD PTR [rbp-0x8] #h
0x0000555555555231 <+102>:	push   rdi #将h保存到栈中
0x0000555555555232 <+103>:	mov    edi,DWORD PTR [rbp-0xc] #g
0x0000555555555235 <+106>:	push   rdi #将g保存到栈中
```

我们看到，多余的参数g、h、i通过保存在栈中来传递给函数myfunc。

