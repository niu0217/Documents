# C++中虚成员函数调用方式

## 只有一个虚函数

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
    void myfunc(int value) {
        this->m_i += value;
    }
    virtual void vmyfunc() {
        printf("vmyfunc()被调用，this = %p\n", this);
    }
};

int main()
{
    //用对象调用虚函数，和调用普通函数没有区别,不会使用虚函数表
    MYACLS myacls;
    myacls.vmyfunc();

    MYACLS* pmyacls = new MYACLS();
    pmyacls->vmyfunc();
    delete pmyacls;
    pmyacls = nullptr;

    return 0;
}
```

调试：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   21
   22 int main()
   23 {
   24     //用对象调用虚函数，和调用普通函数没有区别,不会使用虚函数表
   25     MYACLS myacls;
 ► 26     myacls.vmyfunc();
   27
   28     MYACLS* pmyacls = new MYACLS();
   29     pmyacls->vmyfunc();
   30     delete pmyacls;
   31     pmyacls = nullptr;
   
=> 0x0000555555555211 <+40>:	lea    rax,[rbp-0x30]
   0x0000555555555215 <+44>:	mov    rdi,rax
   0x0000555555555218 <+47>:	call   0x5555555552fc <MYACLS::vmyfunc()>
```

继续：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   24     //用对象调用虚函数，和调用普通函数没有区别,不会使用虚函数表
   25     MYACLS myacls;
   26     myacls.vmyfunc();
   27
   28     MYACLS* pmyacls = new MYACLS();
 ► 29     pmyacls->vmyfunc();
   30     delete pmyacls;
   31     pmyacls = nullptr;
   32
   33     return 0;
   34 }
   
   # rax = pmyacls = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   # rax中的值0x55555556b2c0又被叫做this指针
=> 0x0000555555555244 <+91>:	mov    rax,QWORD PTR [rbp-0x38]
   # rax = [rax] = [this指针] = [0x55555556b2c0] = 0x0000555555557d70 = 虚表指针 = vptr
   0x0000555555555248 <+95>:	mov    rax,QWORD PTR [rax]
   # rdx = [rax] = [0x0000555555557d70] = 0x00005555555552fc = vptr[0] = MYACLS::vmyfunc()的函数指针
   0x000055555555524b <+98>:	mov    rdx,QWORD PTR [rax]
   # rax = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x000055555555524e <+101>:	mov    rax,QWORD PTR [rbp-0x38]
   # rdi = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x0000555555555252 <+105>:	mov    rdi,rax
   # call MYACLS::vmyfunc()的函数指针
   0x0000555555555255 <+108>:	call   rdx
   
# 虚函数表的样子
# pmyacls = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
# vptr = 0x555555557d70 = 虚表指针 = vptr
# vptr[0] = 0x5555555552fc = [0x555555557d70 + 0x0] = MYACLS::vmyfunc()的函数指针
pwndbg> info vtbl pmyacls
vtable for 'MYACLS' @ 0x555555557d70 (subobject @ 0x55555556b2c0):
[0]: 0x5555555552fc <MYACLS::vmyfunc()>

# pmyacls = 0x55555556b2c0
pwndbg> p pmyacls
$1 = (MYACLS *) 0x55555556b2c0

# vptr = 0x555555557d70
pwndbg> x/gx 0x55555556b2c0
0x55555556b2c0:	0x0000555555557d70

# vptr[0] = 0x5555555552fc = [0x555555557d70 + 0x0] = MYACLS::vmyfunc()的函数指针
pwndbg> x/gx 0x0000555555557d70
0x555555557d70 <vtable for MYACLS+16>:	0x00005555555552fc
pwndbg> info line *0x00005555555552fc
Line 17 of "test.cpp" starts at address 0x5555555552fc <MYACLS::vmyfunc()> and ends at 0x55555555530c <MYACLS::vmyfunc()+16>.
```

## 有4个虚函数

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
    void myfunc() {
        printf("myfunc()被调用，this = %p\n", this);
    }
    virtual void vmyfunc1() {
        printf("vmyfunc1()被调用，this = %p\n", this);
    }
    virtual void vmyfunc2() {
        printf("vmyfunc2()被调用，this = %p\n", this);
    }
    virtual void vmyfunc3() {
        printf("vmyfunc3()被调用，this = %p\n", this);
    }
    virtual void vmyfunc4() {
        printf("vmyfunc4()被调用，this = %p\n", this);
    }
};

int main()
{
    //用对象调用虚函数，和调用普通函数没有区别,不会使用虚函数表
    MYACLS myacls;
    myacls.myfunc();
    myacls.vmyfunc1();
    myacls.vmyfunc2();
    cout<<endl;

    MYACLS* pmyacls = new MYACLS();
    pmyacls->myfunc();
    pmyacls->vmyfunc1();
    pmyacls->vmyfunc2();
    pmyacls->vmyfunc3();
    pmyacls->vmyfunc4();

    delete pmyacls;
    pmyacls = nullptr;

    return 0;
}
```

调试：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   30
   31 int main()
   32 {
   33     //用对象调用虚函数，和调用普通函数没有区别,不会使用虚函数表
   34     MYACLS myacls;
 ► 35     myacls.myfunc();
   36     myacls.vmyfunc1();
   37     myacls.vmyfunc2();
   38     cout<<endl;
   39
   40     MYACLS* pmyacls = new MYACLS();
   
   # myacls.myfunc();
=> 0x0000555555555231 <+40>:	lea    rax,[rbp-0x30]
   0x0000555555555235 <+44>:	mov    rdi,rax
   0x0000555555555238 <+47>:	call   0x55555555539a <MYACLS::myfunc()>
   
   # myacls.vmyfunc1();
   0x000055555555523d <+52>:	lea    rax,[rbp-0x30]
   0x0000555555555241 <+56>:	mov    rdi,rax
   0x0000555555555244 <+59>:	call   0x5555555553c6 <MYACLS::vmyfunc1()>
   
   # myacls.vmyfunc2();
   0x0000555555555249 <+64>:	lea    rax,[rbp-0x30]
   0x000055555555524d <+68>:	mov    rdi,rax
   0x0000555555555250 <+71>:	call   0x5555555553f2 <MYACLS::vmyfunc2()>
```

从这段汇编代码我们看到，用对象调用虚函数，和调用普通函数没有区别,不会使用虚函数表。

继续：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   36     myacls.vmyfunc1();
   37     myacls.vmyfunc2();
   38     cout<<endl;
   39
   40     MYACLS* pmyacls = new MYACLS();
 ► 41     pmyacls->myfunc();
   42     pmyacls->vmyfunc1();
   43     pmyacls->vmyfunc2();
   44     pmyacls->vmyfunc3();
   45     pmyacls->vmyfunc4();
   46
   
   # pmyacls->myfunc();
=> 0x0000555555555292 <+137>:	mov    rax,QWORD PTR [rbp-0x38]
   0x0000555555555296 <+141>:	mov    rdi,rax
   0x0000555555555299 <+144>:	call   0x55555555539a <MYACLS::myfunc()>
   
   
   # pmyacls->vmyfunc1();
   # rax = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x000055555555529e <+149>:	mov    rax,QWORD PTR [rbp-0x38]
   # rax = [this指针] = [0x55555556b2c0 + 0x0] = vptr = 0x555555557d48 = 虚表指针
   0x00005555555552a2 <+153>:	mov    rax,QWORD PTR [rax]
   # rdx = vptr[0] = 0x5555555553c6 = [0x555555557d48 + 0x0] = MYACLS::vmyfunc1()
   0x00005555555552a5 <+156>:	mov    rdx,QWORD PTR [rax]
   # rax = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552a8 <+159>:	mov    rax,QWORD PTR [rbp-0x38]
   # rdi = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552ac <+163>:	mov    rdi,rax
   # call MYACLS::vmyfunc1()
   0x00005555555552af <+166>:	call   rdx
   
   
   # pmyacls->vmyfunc2();
   # rax = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552b1 <+168>:	mov    rax,QWORD PTR [rbp-0x38]
   # rax = [this指针] = [0x55555556b2c0 + 0x0] = vptr = 0x555555557d48 = 虚表指针
   0x00005555555552b5 <+172>:	mov    rax,QWORD PTR [rax]
   # rax = &vptr[1] = 0x555555557d48 + 0x8
   0x00005555555552b8 <+175>:	add    rax,0x8
   # rdx = vptr[1] = 0x5555555553f2 = [0x555555557d48 + 0x8] = MYACLS::vmyfunc2()
   0x00005555555552bc <+179>:	mov    rdx,QWORD PTR [rax]
   # rax = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552bf <+182>:	mov    rax,QWORD PTR [rbp-0x38]
   # rdi = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552c3 <+186>:	mov    rdi,rax
   # call MYACLS::vmyfunc2()
   0x00005555555552c6 <+189>:	call   rdx
   
   
   # pmyacls->vmyfunc3();
   # rax = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552c8 <+191>:	mov    rax,QWORD PTR [rbp-0x38]
   # rax = [this指针] = [0x55555556b2c0 + 0x0] = vptr = 0x555555557d48 = 虚表指针
   0x00005555555552cc <+195>:	mov    rax,QWORD PTR [rax]
   # rax = &vptr[2] = 0x555555557d48 + 0x10
   0x00005555555552cf <+198>:	add    rax,0x10
   # rdx = vptr[2] = 0x55555555541e = [0x555555557d48 + 0x10] = MYACLS::vmyfunc3()
   0x00005555555552d3 <+202>:	mov    rdx,QWORD PTR [rax]
   # rax = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552d6 <+205>:	mov    rax,QWORD PTR [rbp-0x38]
   # rdi = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552da <+209>:	mov    rdi,rax
   # call MYACLS::vmyfunc3()
   0x00005555555552dd <+212>:	call   rdx
   
   
   # pmyacls->vmyfunc4();
   # rax = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552df <+214>:	mov    rax,QWORD PTR [rbp-0x38]
   # rax = [this指针] = [0x55555556b2c0 + 0x0] = vptr = 0x555555557d48 = 虚表指针
   0x00005555555552e3 <+218>:	mov    rax,QWORD PTR [rax]
   # rax = &vptr[3] = 0x555555557d48 + 0x18
   0x00005555555552e6 <+221>:	add    rax,0x18
   # rdx = vptr[3] = 0x55555555544a = [0x555555557d48 + 0x18] = MYACLS::vmyfunc4()
   0x00005555555552ea <+225>:	mov    rdx,QWORD PTR [rax]
   # rax = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552ed <+228>:	mov    rax,QWORD PTR [rbp-0x38]
   # rdi = this指针 = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
   0x00005555555552f1 <+232>:	mov    rdi,rax
   # call MYACLS::vmyfunc4()
   0x00005555555552f4 <+235>:	call   rdx
```

```assembly
# 虚函数表的样子
# pmyacls = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
# vptr = [0x55555556b2c0 + 0x0] = 0x555555557d48 = 虚表指针
# vptr[0] = 0x5555555553c6 = [0x555555557d48 + 0x0] = MYACLS::vmyfunc1()
# vptr[1] = 0x5555555553f2 = [0x555555557d48 + 0x8] = MYACLS::vmyfunc2()
# vptr[2] = 0x55555555541e = [0x555555557d48 + 0x10] = MYACLS::vmyfunc3()
# vptr[3] = 0x55555555544a = [0x555555557d48 + 0x18] = MYACLS::vmyfunc4()
pwndbg> info vtbl pmyacls
vtable for 'MYACLS' @ 0x555555557d48 (subobject @ 0x55555556b2c0):
[0]: 0x5555555553c6 <MYACLS::vmyfunc1()>
[1]: 0x5555555553f2 <MYACLS::vmyfunc2()>
[2]: 0x55555555541e <MYACLS::vmyfunc3()>
[3]: 0x55555555544a <MYACLS::vmyfunc4()>


# pmyacls = 0x55555556b2c0 = 在堆上申请的一个MYACLS对象的地址
pwndbg> p pmyacls
$2 = (MYACLS *) 0x55555556b2c0

# vptr = [0x55555556b2c0 + 0x0] = 0x555555557d48 = 虚表指针
pwndbg> x/gx 0x55555556b2c0
0x55555556b2c0:	0x0000555555557d48

# vptr[0] = 0x5555555553c6 = [0x555555557d48 + 0x0] = MYACLS::vmyfunc1()
# vptr[1] = 0x5555555553f2 = [0x555555557d48 + 0x8] = MYACLS::vmyfunc2()
# vptr[2] = 0x55555555541e = [0x555555557d48 + 0x10] = MYACLS::vmyfunc3()
# vptr[3] = 0x55555555544a = [0x555555557d48 + 0x18] = MYACLS::vmyfunc4()
pwndbg> x/4gx 0x0000555555557d48
0x555555557d48 <vtable for MYACLS+16>:	0x00005555555553c6	0x00005555555553f2
0x555555557d58 <vtable for MYACLS+32>:	0x000055555555541e	0x000055555555544a
```

