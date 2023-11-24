# GDB调试

## 汇编王牌

生成32位的汇编代码：

```shell
gcc -fno-asynchronous-unwind-tables -fno-exceptions -no-pie -fno-pic -m32 ./test.c -o test
```

生成64位的汇编代码：

```shell
gcc -fno-asynchronous-unwind-tables -fno-exceptions -no-pie -fno-pic -m64 ./test.c -o test
```

解析编译选项：

+ `-fno-asynchronous-unwind-tables `-->汇编代码中不生成.cfi开头的代码
+ `-fno-exceptions`-->禁用异常机制
+ `-fno-stack-protector`-->不使用栈保护者



## 常用的gdb命令

查看栈帧：`frame/f`

查看堆栈情况：`backtrace/bt`

查看寄存器：

+ 查看所有的寄存器：`i r a`
+ 查看ebp、esp：`i r ebp esp`

查看分配的chunk：`heap`

查看分配的栈：`stack`

查看内存分配情况：`vmmap`

查看全局和静态变量：`info variables`

查看当前栈帧的局部变量：`info locals`

查看当前栈帧的参数：`info args`

查看指令地址0x56556280所对应的在源代码中的位置：`info line *0x56556280`

打印数组的10个元素：`p *array@10`



## 常用的pwngdb命令

使用x命令查看内存的内容：

+ 形式：`x/FMT ADDRESS`，其中FMT中三部分组成：count format size(format与size的参数位置可以互换）
+ format：
  + o：octal, 即八进制
  + x：hex, 十六进制
  + d：decimal, 十进制
  + u：unsigned decimal
  + t：binary, 二进制
  + f：float, 符号数
  + a：address, 地址的形式
  + c：char类型
  + s：string
  + z：hes, zero padded on the left
+ size：
  + b：byte, 一个字节大小
  + h：2个字节
  + w：4个字节
  + g：giant, 8个字节
+ 举例：
  + 查看内存地址0x80491e7开始的4条指令信息：`x/4i 0x80491e7`
  + 查看从内存地址0xffffda88开始8个字节的内存数据。16进制显示：`x/2x 0xffffda88`或者`x/gx 0xffffda88`
  + 查看从内存地址0xffffda88开始8个字节的内存数据。10进制显示：`x/2d 0xffffda88`
  + 查看从内存地址0xffffda8开始的6个8字节的内存数据。16进制显示：`x/6gx 0xffffda8`

优雅地显示内存信息：`dps 0xffffdaf0`

打印函数信息：`disassemble func`

查看程序保护机制：`checksec`



## 涉及的Linux命令

root用户：

+ 切换到root用户：`su`
+ 退出root用户：`exit`

查看当前运行的进程：`ps aux | grep 程序名字`

查看当前运行的轻量级进程：`ps -aL | grep 程序名字`

查看主线程和子线程的关系：`pstree -p 主线程id`



## 基本调试命令

### 运行

`run`-->命令缩写：r  开始运行程序，程序运行到断点的位置就会停下来，如果没有遇到断点，程序一直运行下去

`continue`-->命令缩写：c  继续程序运行，直到遇到下一个断点

`next`-->命令缩写：n  执行当前行语句，如果该语句为函数调用，不会进入函数内部执行

`step`-->命令缩写：s  执行当前行语句，如果该语句为函数调用，则进入函数执行其中的第一条语句。特别注意：如果函数是库函数或第三方提供的函数，用s是进不去的，因为没有源代码，如果是你自己定义的函数，只要有源码就可以进去。

`until`-->运行程序直到退出循环体; / until+行号： 运行至某行

`finish`-->运行程序，直到当前函数完成返回，并打印函数返回时的堆栈地址和返回值及参数值等信息。

`call 函数(参数)`-->调用“函数”，并传递“参数”，如：call gdb_test(55)

`quit`-->命令缩写：q. 退出gdb环境



### 设置断点

代码断点：

+ 代码断点是最常用的，是用于设置断点到程序的特定地址，特定地址可以用代码行号、函数名、地址值等来指定，可以设置一次断点和条件断点。
+ 设置普通断点：`break location`
+ 设置一次断点，也称为临时断点，断下来后会自动将该断点删除：`tbreak location`
+ 设置条件断点，只有满足condition条件后才会断下来，condition是boolean表达式：`break location if condition`。举例： `b watch.c:7 if i == 8`

内存断点：

+ 代码断点是以代码为对象进行监控跟踪，而内存断点则是以内存为对象。对内存值进行监控，根据监控类型分为：监控内存值改变(watch)，监控内存值被读取(rwatch)和监控内存值读取或写入(awatch)。
+ 监控内存值改变：`watch expr [if condition]`。举例：`watch i if i == 8`
+ 监控内存值被读取：`rwatch expr [if condition]`
+ 监控内存值被读取和写入：`awatch expr [if condition]`
+ 注释：expr 可以是变量也可以是表达式，但要确保有对应的内存地址，不能是常量。在使用变量时确保该变量在当前所在的上下文中。同样也可以添加if条件。

事件断点：

+ 事件断点用于监听特殊事件发生，如发生则中断下来
+ C++ exception，使用 `catch exception [name]`
+ Ada exception，使用 `catch handlers [name]`
+ exec事件， 使用 `catch exec`
+ fork事件， 使用 `catch fork` 或者 `catch vfork`
+ 加载和卸载动态so事件， 使用` catch load|unload [regexp]`
+ 监听系统信号，使用 `catch signal [signal]`
+ 监听系统调用， 使用 `catch syscall [name|number|group:groupname|g:groupname] …`
  + 举例：查看printf的输出  `catch syscall write`

补充：

+ 设置断点时显示的信息：
  + 编号
  + 类型
  + 显示
  + enable状态
  + 断点地址
  + 描述
+ `break n（简写b n）`：在第n行处设置断点 ;可以带上代码路径和代码名称： b OAGUPDATE.cpp:578
+ `break func`：在函数func()的入口处设置断点，如：break cb_button
+ `delete 断点号n`：删除第n个断点
+ `disable 断点号n`：暂停第n个断点
+ `enable 断点号n`：开启第n个断点
+ `clear 行号n`：清除第n行的断点
+ `info breakpoints`（简写info b）：显示当前程序的断点设置情况



### 查看源代码

`list（简写l）`：列出程序的源代码，默认每次显示10行

`list 行号`：将显示当前文件以“行号”为中心的前后10行代码，如：list 12

`list 函数名`：将显示“函数名”所在函数的源代码，如：list main

`list`：不带参数，将接着上一次 list 命令的，输出下边的内容

### 打印表达式

`print 表达式`：简记为 p ，其中“表达式”可以是任何当前正在被测试程序的有效表达式，比如当前正在调试C语言的程序，那么“表达式”可以是任何C语言的有效表达式，包括数字，变量甚至是函数调用。

`print a`：将显示整数 a 的值

`print ++a`：将把 a 中的值加1,并显示出来

`print name`：将显示字符串 name 的值

`print gdb_test(22)`：将以整数22作为参数调用 gdb_test() 函数

`print gdb_test(a)`：将以变量 a 作为参数调用 gdb_test() 函数

`display 表达式`：在单步运行时将非常有用，使用display命令设置一个表达式后，它将在每次单步进行指令后，紧接着输出被设置的表达式及值。如：` display a`

`watch 表达式`：设置一个监视点，一旦被监视的“表达式”的值改变，gdb将强行终止正在被调试的程序。如： `watch a`

### 查询运行信息

当前运行的堆栈列表：`where/bt`

指定运行时的参数：`set args 参数`

查看设置好的参数：`show args`

来查看程序的是否在运行，进程号，被暂停的原因：`info program`

查看汇编代码：`disassemble`

### 分割窗口

`layout`：用于分割窗口，可以一边查看代码，一边测试

`layout src`：显示源代码窗口

`layout asm`：显示反汇编窗口

`layout regs`：显示源代码/反汇编和CPU寄存器窗口

`layout split`：显示源代码和反汇编窗口

`ctrl + l`：刷新窗口

`ctrl + x + a`：回到传统模式，即退出layout，回到执行layout之前的调试窗口

在TUI模式下：

+ `ctrl+p` previous 上一条命令
+ `ctrl+n` next 下一条命令
+ `focus next` 编辑bash
+ `focus prev` 编辑代码



## 调试core文件

什么是core文件？

+ 在Linux下程序不寻常退出时，内核会在当前工作目录下生成一个core文件（是一个内存映像，同时加上调试信息）。使用gdb来查看core文件，可以指示出导致程序出错的代码所在文件和行数。

命令：

+ `ulimit -a`：检查生成core文件的选项是否打开
+ `ulimit -c unlimited`：程序会生成core文件
+ `ulimit -c 0`：程序不会生成core文件
+ `gdb + 可执行程序 + core文件`：显示出错的代码
+ `sudo bash -c "echo core > /proc/sys/kernel/core_pattern "`：指定core文件生成在当前目录下
+ `bt`：显示调用栈



## 调试正在运行的程序

假设：

+ 运行的程序：hello
+ 进程号：65772

查看运行的程序的进程号：`ps -aux | grep hello`

切换到root用户：`su`

此时运行的程序会中断，等待你的调试;如果想要程序继续执行，那就退出gdb调试：`gdb hello -p 65772`



## 调试多进程程序

调试父进程：`set follow-fork-mode parent` (默认就是调试父进程)

调试子进程：`set follow-fork-mode child`

设置调试模式：

+ `set detach-on-fork on` (默认是on). 表示调试当前进程的时候，其它的进程继续运行
+ `set detach-on-fork off`。表示调试当前进程的时候，其它的进程被gdb挂起

查看调试的进程：`info inferiors`

切换当前调试的进程：`inferior 进程id`



## 调试多线程程序

查看线程：`info threads`

切换线程：`thread 线程id`

只运行当前线程：`set scheduler-locking on`

运行全部的线程：`set scheduler-locking off`

指定某线程执行某gdb命令：`thread apply 线程id cmd`

全部的线程执行某gdb命令：`thread apply all cmd`