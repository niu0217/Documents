# C++中类的静态成员变量分析

静态成员变量可以当做一个全局变量，但是它只在类的空间内可见。也就是说：

+ 生命周期：静态成员变量拥有全局变量的生命周期；
+ 作用域：静态成员变量作用域局限在一个类中；
+ 在可执行文件中的位置：如果初始化了并且不为0，则位于`.data`节；如果没有初始化或者初始化为0，则位于`.bss`节；

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
};

int MYACLS::m_si = 10; //定义

int main()
{
    MYACLS myobj;
    MYACLS* pmyobj = new MYACLS();

    cout<<MYACLS::m_si<<endl;
    //特别注意：m_si是属于类的，对象可有可无都没区别
    cout<<myobj.m_si<<endl;
    cout<<pmyobj->m_si<<endl;

    MYACLS::m_si = 1;
    myobj.m_si = 2;
    pmyobj->m_si = 3;

    return 0;
}
```

调试：

```bash
In file: /home/ubuntu/Dev/C++ObjectModern/data_semantics/test.cpp
   20     cout<<MYACLS::m_si<<endl;
   21     //特别注意：m_si是属于类的，对象可有可无都没区别
   22     cout<<myobj.m_si<<endl;
   23     cout<<pmyobj->m_si<<endl;
   24
 ► 25     MYACLS::m_si = 1;
   26     myobj.m_si = 2;
   27     pmyobj->m_si = 3;
   28
   29     return 0;
   30 }

=> 0x000055555555526b <+162>:	mov    DWORD PTR [rip+0x2d9b],0x1        # 0x555555558010 <MYACLS::m_si>
   0x0000555555555275 <+172>:	mov    DWORD PTR [rip+0x2d91],0x2        # 0x555555558010 <MYACLS::m_si>
   0x000055555555527f <+182>:	mov    DWORD PTR [rip+0x2d87],0x3        # 0x555555558010 <MYACLS::m_si>
```

我们通过反汇编代码看到：

```c++
MYACLS::m_si = 1;
myobj.m_si = 2;
pmyobj->m_si = 3;
```

这3种调用方式没有任何区别，都是给`0x555555558010 <MYACLS::m_si>`赋值。

