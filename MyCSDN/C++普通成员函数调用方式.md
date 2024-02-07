# C++普通成员函数调用方式

C++设计的时候有一个要求：要求对普通成员函数的调用不应该比全局函数效率差；

基于这种设计要求，编译器内部实际上是将对成员函数的调用转换成了对全局函数的调用。

成员函数有独立的地址，是和类相关的，并且成员函数的地址，是在编译的时候就确定好了的。

```c++
/* ************************************************************************
> File Name:     test.cpp
> Author:        niu0217
> Created Time:  Tue 06 Feb 2024 08:54:26 PM CST
> Description:
 ************************************************************************/

#include<iostream>
using namespace std;

class MYACLS {
public:
    int m_i;
    //myfunc的实际样子：myfunc(MYACLS* const this, int value)
    void myfunc(int value) {
        this->m_i += value;
    }
};

void gmyfunc(MYACLS* pobj, int value) {
    pobj->m_i += value;
}

int main()
{
    MYACLS myacls;
    myacls.myfunc(18);
    gmyfunc(&myacls, 18);

    return 0;
}
```

调试：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   22 }
   23
   24 int main()
   25 {
   26     MYACLS myacls;
 ► 27     myacls.myfunc(18);
   28     gmyfunc(&myacls, 18);
   29
   30     return 0;
   31 }
   
pwndbg> disassemble
Dump of assembler code for function main():
   0x00005555555551ac <+0>:	endbr64
   0x00005555555551b0 <+4>:	push   rbp
   0x00005555555551b1 <+5>:	mov    rbp,rsp
   0x00005555555551b4 <+8>:	sub    rsp,0x10
   0x00005555555551b8 <+12>:	mov    rax,QWORD PTR fs:0x28
   0x00005555555551c1 <+21>:	mov    QWORD PTR [rbp-0x8],rax
   0x00005555555551c5 <+25>:	xor    eax,eax
=> 0x00005555555551c7 <+27>:	lea    rax,[rbp-0xc]
   0x00005555555551cb <+31>:	mov    esi,0x12
   0x00005555555551d0 <+36>:	mov    rdi,rax
   0x00005555555551d3 <+39>:	call   0x55555555526a <MYACLS::myfunc(int)>
   0x00005555555551d8 <+44>:	lea    rax,[rbp-0xc]
   0x00005555555551dc <+48>:	mov    esi,0x12
   0x00005555555551e1 <+53>:	mov    rdi,rax
   0x00005555555551e4 <+56>:	call   0x555555555189 <gmyfunc(MYACLS*, int)>
   0x00005555555551e9 <+61>:	mov    eax,0x0
   0x00005555555551ee <+66>:	mov    rdx,QWORD PTR [rbp-0x8]
   0x00005555555551f2 <+70>:	xor    rdx,QWORD PTR fs:0x28
   0x00005555555551fb <+79>:	je     0x555555555202 <main()+86>
   0x00005555555551fd <+81>:	call   0x555555555080 <__stack_chk_fail@plt>
   0x0000555555555202 <+86>:	leave
   0x0000555555555203 <+87>:	ret
End of assembler dump.
```

分析：

```assembly
   # myacls.myfunc(18);
=> 0x00005555555551c7 <+27>:	lea    rax,[rbp-0xc]
   0x00005555555551cb <+31>:	mov    esi,0x12
   0x00005555555551d0 <+36>:	mov    rdi,rax
   0x00005555555551d3 <+39>:	call   0x55555555526a <MYACLS::myfunc(int)>
   
   # gmyfunc(&myacls, 18);
   0x00005555555551d8 <+44>:	lea    rax,[rbp-0xc]
   0x00005555555551dc <+48>:	mov    esi,0x12
   0x00005555555551e1 <+53>:	mov    rdi,rax
   0x00005555555551e4 <+56>:	call   0x555555555189 <gmyfunc(MYACLS*, int)>
```

我们看到类成员函数`myfunc`和全局函数`gmyfunc`的汇编代码一模一样。这是为什么呢？

原来这里面和编译器的设计有关：

+ 实际的类成员函数`myfunc`的样子：`void myfunc(MYACLS* const this, int value)`
+ 全局函数`gmyfunc`的样子：`void gmyfunc(MYACLS* pobj, int value)`

我们发现区别并不大。所以这就是为什么汇编代码一模一样的原因。