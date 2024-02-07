# C++静态成员函数调用方式

## 引入

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
    static void smyfunc() {
        printf("smyfunc()被调用\n");
    }
};

int main()
{
    MYACLS myacls;
    myacls.smyfunc();
    MYACLS::smyfunc();
    cout<<endl;

    MYACLS* pmyacls = new MYACLS();
    pmyacls->smyfunc();

    delete pmyacls;
    pmyacls = nullptr;

    return 0;
}
```

调试：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   20 };
   21
   22 int main()
   23 {
   24     MYACLS myacls;
 ► 25     myacls.smyfunc();
   26     MYACLS::smyfunc();
   27     cout<<endl;
   28
   29     MYACLS* pmyacls = new MYACLS();
   30     pmyacls->smyfunc();
   
=> 0x00005555555551d5 <+12>:	call   0x55555555527b <MYACLS::smyfunc()>
   0x00005555555551da <+17>:	call   0x55555555527b <MYACLS::smyfunc()>
```

这其中没有`this`指针。并且`myacls.smyfunc();`和`MYACLS::smyfunc();`没有区别。

继续：

```assembly
In file: /home/ubuntu/Dev/C++ObjectModern/function_semantics/test.cpp
   25     myacls.smyfunc();
   26     MYACLS::smyfunc();
   27     cout<<endl;
   28
   29     MYACLS* pmyacls = new MYACLS();
 ► 30     pmyacls->smyfunc();
   31
   32     delete pmyacls;
   33     pmyacls = nullptr;
   34
   35     return 0;
   
=> 0x0000555555555209 <+64>:	call   0x55555555527b <MYACLS::smyfunc()>
```

对比前面我们看出，这3种调用方式完全没区别。

## 为什么静态成员函数没有this指针？

静态成员函数的特征：

+ 生命周期：和类的生命周期一样；
+ 所属：静态成员函数属于类，而不属于类对象；

我们知道`this`指针和类的对象有关，而静态成员函数只与类有关，和类对象没有关系。

因此静态成员函数中没有`this`指针。

