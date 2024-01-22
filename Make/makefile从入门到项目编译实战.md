# makefile从入门到项目编译实战

## 1. make常用选项

```makfile
make[-f file][options][target]

#没有指定目标时，默认使用第一个目标
#如果指定，则执行对应的命令
```

make默认在当前目录中寻找GNUmakefile，makefile，Makefile的文件作为make的输入文件
```
-f 可以指定除上述文件名之外的文件作为输入文件
-v 显示版本号
-n 只输出命令，但不执行，一般用来测试
-s 只执行命令，但不显示具体命令，此处可在命令中用@抑制命令输出
-w 显示执行前执行后的路径
-C dir 指定makeflie所在的目录
```



## 2. gcc/g++ 编译流程

```makefile
gcc -lstdc++ main.cpp

#把过程拆分
#预处理	gcc -E main.cpp >main.ii
#编译		gcc -S main.ii		 得到名为main.s的汇编文件
#汇编   gcc -c main.s		 得到名为main.o(.obj)的二进制文件
#链接   gcc -lstdc++ main.o  得到名为a.out的可执行文件
```



## 3. makefile中的变量

**系统变量**

```makefile
$* #不包括扩展名的目标文件名称
$+ #所有的依赖文件，以空格分隔
$< #表示规则中的第一个条件
$? #所有时间戳比目标文件晚的依赖文件，以空格分隔
$@ #目标文件的完整名称
$^ #所有不重复的依赖文件，以空格分隔
$% #如果目标是归档成员，则该变量表示目标的归档成员名称
```

```makefile
calc:add.o sub.o multi.o calc.o
	gcc $^ -o $@
	
add.o:add.cpp
	gcc -c $^ -o $@

sub.o:sub.cpp
	gcc -c $^ -o $@
	
multi.o:multi.cpp
	gcc -c $^ -o $@
	
calc.o:calc.cpp
	gcc -c $^ -o $@
	
clean:
	rm -f *.o calc
```

**系统常量（可用make -p查看）**

```makefile
AS	#汇编程序的名称，默认为as
CC	#C编译器名称，默认为cc
CPP	#C预编译器名称，默认为cc -E
CXX	#C++编译器名称，默认为g++
RM	#文件删除程序别名，默认rm -f
```

```makefile
#$(CC)可替换为$(CXX)，因为$(CXX)可实现跨平台
calc:add.o sub.o multi.o calc.o
	$(CC) add.o sub.o multi.o calc.o -o calc
	
add.o:add.cpp
	$(CC) -c add.cpp -o add.o

sub.o:sub.cpp
	$(CC) -c sub.cpp -o sub.o
	
multi.o:multi.cpp
	$(CC) -c multi.cpp -o multi.o
	
calc.o:calc.cpp
	$(CC) -c calc.cpp -o calc.o
	
clean:
	$(RM) *.o calc
```

**自定义变量**

```
定义：变量名=变量值
使用：$(变量名)/${变量名}
```

```makefile
OBJ = add.o sub.o multi.o calc.o
TARGET = calc

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
	
add.o:add.cpp
	gcc -c add.cpp -o add.o

sub.o:sub.cpp
	gcc -c sub.cpp -o sub.o
	
multi.o:multi.cpp
	gcc -c multi.cpp -o multi.o
	
calc.o:calc.cpp
	gcc -c calc.cpp -o calc.o
	
clean:
	rm -f *.o $(TARGET)
```



## 4. makefile 中的伪目标和模式匹配

### 4.1 伪目标

```makefile
.PHONY:目标	
#声明目标为伪目标之后，makefile将不会判断目标是否存在或该目标是否需要更新
```

如果项目路径中有与**clean**同名的文件，**`make clean`命令无法执行，需要在makefile**文件中添加**`.PHONY:clean`**，才能使命令正常执行

```makefile
.PHONY:clean
OBJ = add.o sub.o multi.o calc.o
TARGET = calc

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
	
add.o:add.cpp
	gcc -c add.cpp -o add.o

sub.o:sub.cpp
	gcc -c sub.cpp -o sub.o
	
multi.o:multi.cpp
	gcc -c multi.cpp -o multi.o
	
calc.o:calc.cpp
	gcc -c calc.cpp -o calc.o
	
clean:
	rm -f *.o $(TARGET)
```

### 4.2 模式匹配

```
%目标:%依赖	#目标和依赖相同部分，可以用%来通配
```

依赖中的**`add.o sub.o multi.o calc.o`**都可以通过使用**`%.o:%.cpp`**产生

```makefile
OBJ = add.o sub.o multi.o calc.o
TARGET = calc

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
	
%.o:%.cpp
	gcc -c $^ -o $@
	
clean:
	rm -f *.o $(TARGET)
```

**- makefile 内置函数**

```makefile
$(wildcard 文件列表)	#获取对应文件路径下的对应模式的文件名
$(patsubst 源模式, 目标模式, 文件列表)	#将文件列表中想要改变的源模式替换成想要的目标模式
```

```makefile
#OBJ = add.o sub.o multi.o calc.o
OBJ = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
TARGET = calc

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
	
%.o:%.cpp
	gcc -c $^ -o $@
	
clean:
	rm -f *.o $(TARGET)
```



## 5. makefile运行流程

<img src="https://img-blog.csdnimg.cn/5f2ceadab86b4b17b911e81fc95a5d0e.png#pic_center" alt="在这里插入图片描述" style="zoom:50%;" /> 



## 6. makefile中编译动态链接库

动态链接库：不会把代码编译到二进制文件中，而是在运行时才去加载，所以需要维护一个地址。

- **动态**：动态加载，运行时才加载
- **链接**：指库文件和二进制程序分离，用某种手段维护两者之间的关系
- 库：库文件
  - **Windows** 中后缀为 **.dll**
  - **Linux** 中后缀为 **.so**
- **常用选项**

```
-fPIC 产生位置无关的代码
-shared 共享
-l 指定动态库
-I 指定头文件目录，默认当前目录
-L 手动指定库文件搜索目录，默认只链接共享目录
```

**优点：**

程序可以和库文件分离，可以分别发版，然后库文件可以被多处共享。

### 6.1 代码的目录结构

+ TestCode:
  + main.cpp
  + SoTest.h
  + 001:
    + SoTest.h
    + SoTest.cpp
    + Test.cpp
    + makefile
    + libSoTest.so

### 6.2 发布前

#### SoTest.h

```c++
class SoTest{
public:
    void func1();
    virtual void func2();
    virtual void func3() = 0;
};
```

#### SoTest.cpp

```c++
#include <iostream>
#include "SoTest.h"

void SoTest::func1(){
    printf("func1\n");
}

void SoTest::func2(){
    printf("func2\n");
}

void SoTest::func3(){
    printf("func3\n");
}
```

```bash
g++ -shared -fPIC SoTest.cpp -o libSoTest.so
```

#### Test.cpp

```c++
#include <iostream>
#include "SoTest.h"

class Test:public SoTest{
public:
    void func2(){
        printf("Test-func2\n");
    }
    void func3(){
        printf("Test-func3\n");
    }
};

int main(){
    Test t1;
    t1.func1();
    t1.func2();
    t1.func3();
    
    return 0;
}
```

```bash
g++ -lSoTest -L./ Test.cpp -o Test
```

### 6.3 发布后

#### SoTest.h

```c++
class SoTest{
public:
    void func1();
    virtual void func2();
    virtual void func3() = 0;
};
```

#### main.cpp

```c++
#include <iostream>
#include "SoTest.h"

class MainTest:public SoTest{
public:
    void func2(){
        printf("MainTest-func2\n");
    }
    void func3(){
        printf("MainTest-func3\n");
    }
};

int main(){
    MainTest t1;
    t1.func1();
    t1.func2();
    t1.func3();
    
    return 0;
}

```

```bash
g++ -lSoTest -L./001 main.cpp -o main
```

编译时指定了要依赖的动态库，但运行时，会无法找到**.so**文件

**解决方法：**

- 将动态库文件移动到**main.cpp**文件同级目录下

- 运行时手动指定动态库文件所在目录

  + Linux环境下的命令

    ```bash
    LD_LIBRARY_PATH = ./001
    export LD_LIBRARY_PATH
    ```

  + Mac环境下的命令

    ```bash
    DYLD_LIBRARY_PATH=./001
    export DYLD_LIBRARY_PATH
    ```

### 6.4 001/makefile

```makefile
Test:libSoTest.so
	$(CXX) -lSoTest -L./ Test.cpp -o Test
	cp libSoTest.so /usr/lib  #路径最好为main.cpp同级目录
libsoTest.so:
	$(CXX) -shared -fPIC soTest.cpp -o libSoTest.so
	
clean:
	$(RM) *.so Test
```

- `cp libsoTest.so /usr/lib`将动态库文件复制到动态链接库默认路径下 **不推荐复制，污染原库环境**
- **Linux** 默认动态库路径配置文件
  - /etc/ld.so.conf
  - /etc/ld.so.conf.d/*.conf



## 7. makefile 中编译静态链接库

静态链接库：会把库中的代码编译到二进制文件中，当程序编译完成后，该库文件可以删除

- **Windows** 中后缀为 **.lib**
- **Linux** 中后缀为 **.a**

**优点：**

运行时速度快（不用去加载库文件）

**缺点：**

程序体积更大，并且库中的内容如果有更新，则需要重新编译生成程序

**对比：**

- 动态链接库必须与程序同时部署，还要保证程序能加载得到库文件
- 静态链接库可以不用部署（已经被加载到程序里面了）

### 7.1 代码的目录结构

+ TestCode:

  + makefile

  + main.cpp
  + SoTest.h
  + aTest.h
  + 001:
    + SoTest.h
    + SoTest.cpp
    + Test.cpp
    + makefile
    + libSoTest.so
  + 002：
    + aTest.h
    + aTest.cpp
    + aTest.o
    + libaTest.a
    + makefile

### 7.2 发布前

#### aTest.h

```c++
class aTest{
public:
    void func1();
};
```

#### aTest.cpp

```c++
#include <iostream>
#include "aTest.h"

void aTest::func1(){
    printf("aTest-func1\n");
}
```

```bash
g++ -c aTest.cpp -o aTest.o
ar -r libaTest.a aTest.o
```

将**aTest.o**加入到**libaTest.a**中。默认的加入方式为append，即**加在库的末尾**

### 7.3 发布后

#### aTest.h

```c++
class aTest{
public:
    void func1();
};
```

#### main.cpp

```c++
#include <iostream>
#include "SoTest.h"
#include "aTest.h"

class MainTest:public SoTest{
public:
    void func2(){
        printf("MainTest-func2\n");
    }
    void func3(){
        printf("MainTest-func3\n");
    }
};

int main(){
    MainTest t1;
    t1.func1();
    t1.func2();
    t1.func3();
    
    printf("\n\n");
    
    aTest t2;
    t2.func1();
    
    return 0;
}
```

- 指定动态库文件**soTest**和静态库文件**aTest**，编译后由**main.cpp**文件产生**main.o**文件

```bash
g++ -lSoTest -L./001 -laTest -L./002 main.cpp -o main
```

+ 生成一个类似于反汇编的文本文档，进入搜索可以找到**aTest::func1()** 的定义，但只能找到**soTest::func1()**、**soTest::func2()**、**soTest::func3()** 的引用

```bash
objdump -DC main>main.txt
```

### 7.4 002/makefile

```makefile
libaTest:
	$(CXX) -c aTest.cpp -o aTest.o
	$(AR) -r libaTest.a aTest.o
	
clean:
	$(RM) *.o *.a
```

### 7.5 makefile

```makefile
TARGET = main
LDFLAGS = -L./001 -L./002
LIBS = -lSoTest -laTest

$(TARGET):
	$(CXX) $(LIBS) $(LDFLAGS) main.cpp -o $(TARGET)
	
clean:
	$(RM) $(TARGET)
```



## 8. makefile 中通用部分做公共文件头

### 8.1 代码结构

+ 001:
  + a.cpp
  + b.cpp
  + c.cpp
  + makefile
+ 002:
  + x.c
  + y.c
  + z.c
  + makefile
+ makefile

### 8.2 具体代码

#### 001/a.cpp

```c++
#include <iostream>

void func_a(){
	printf("func-a.cpp");
}
```

#### 001/b.cpp

```c++
#include <iostream>

void func_b(){
	printf("func-b.cpp");
}
```

#### 001/c.cpp

```c++
extern void func_a();
extern void func_b();

int main(){
  func_a();
  func_b();

  return 0;
}
```

#### 001/makefile

```makefile
TARGET = c

include ../makefile
```

#### 002/x.c

```c++
#include <stdio.h>

void func_x(){
	printf("func-x.c");
}
```

#### 002/y.c

```c++
#include <stdio.h>

void func_y(){
	printf("func-y.c");
}
```

#### 002/z.c

```c++
extern void func_x();
extern void func_y();

int main(){
  func_x();
  func_y();

  return 0;
}
```

#### 002/makefile

```makefile
TARGET = z

include ../makefile
```

#### makefile

```makefile
SOURCE = $(wildcard ./*.cpp ./*.c)
OBJ = $(patsubst %.cpp, %.o, $(SOURCE))
OBJ := $(patsubst %.c, %.o, $(SOURCE))

.PHONY:clean

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@
	
clean:
	$(RM) $(TARGET) $(OBJ)
```



## 9. makefile 中调用 shell 命令

```makefile
FILE = abc

A := $(shell ls ../)
B := $(shell pwd)
C := $(shell if [ ! -f $(FILE) ]; then touch $(FILE); fi;)

a:
	echo $(A)
	echo $(B)
	echo $(C)
	
clean:
	$(RM) $(FILE)
```

- `$(shell ls ../)` 列出上级目录中的所有目录
- `$(shell pwd)` 显示当前所在工作目录的绝对路径
- `$(shell if [ ! -f $(FILE) ]; then touch $(FILE); fi;)` 判断文件是否存在



## 10. makefile 中的嵌套调用和多项目同时编译

源文件为**8. makefile 中通用部分做公共文件头**中的例子用到的:

+ makefile 更名为 makefile-head
+ 001/makefile、002/makefile 中的 include ../makefile 改为include ../makefile-head
+ 新建的makefile 与 makefile-head 在同一级目录下

### 10.1 version1

```makefile
all:
	make -C ./001
	make -c ./002
	
clean:
	make -C ./001 clean
	make -C ./002 clean
```

### 10.2 version2

```makefile
.PHONY:001 002 

DIR = 001 002

all:$(DIR)

$(DIR):
	make -C $@
	
clean:
	echo $(shell for dir in $(DIR); do make -C $$dir clean; done)

```



## 11. makefile 中的条件判断

+ ifeq 判断是否相等，相等返回 true，不相等返回 false
+ ifneq 判断是否不相等，不相等返回 true，相等返回 false
+ ifdef 判断变量是否存在，存在返回 true，不存在返回 false
+ ifndef 判断变量是否不存在，不存在返回 true，存在返回 false

```makefile
A := 123

RS1 :=
RS2 :=
RS3 :=
RS4 :=

ifeq ($(A), 123)
	RS1 := RS1-yes
else
	RS1 := RS1-no
endif

ifneq ($(A), 123)
	RS2 := RS2-yes
else
	RS2 := RS2-no
endif

ifdef A
	RS3 := RS3-yes
else
	RS3 := RS3-no
endif

ifndef A
	RS4 := RS4-yes
else
	RS4 := RS4-no
endif

ifdef FLAG
	FLAG := default
endif

all:
	echo $(RS1)
	echo $(RS2)
	echo $(RS3)
	echo $(RS4)
	echo flag = $(FLAG)
```

- **ifeq**、**ifneq**、**ifdef**、**ifndef** 与条件之间要有空格，不然会报错

- 可以只有 **if**，没有 **else**

  ```bash
  ifdef FLAG
  	FLAG := default
  endif
  ```

- 没有 **elseif** 的用法，如果要实现 **elseif**，就要写嵌套

  ```bash
  ifeq ($(A), 321)
  	RS1 := 321
  else
  	ifeq ($(A), 123)
          RS1 := 123
      else
          RS1 := 0
      endif
  endif
  ```

- 命令行传参

  ```bash
  make -f Makefile FLAG=456
  
  #如果有 Makefile
  make FLAG=456
  ```



## 12. makefile 中的循环

+ **makefile** 中只有一个循环 **foreach**，只支持 **GNU Make**，其他平台的 **make** 需要使用 **shell** 中的循环来实现

```makefile
TARGET = a b c d

all:
	echo $(TARGET)
	echo $(foreach v, $(TARGET), $v)
	echo $(foreach v, $(TARGET), $v.txt)
```

+ **foreach** 可以在循环中逐个的修改值

```makefile
TARGET = a b c d

all:
	touch $(TARGET)
	touch $(foreach v, $(TARGET), $v)
	touch $(foreach v, $(TARGET), $v.txt)
	
clean:
	$(RM) $(TARGET) *.txt
```

```makefile
#循环
#makefile 中只有一个循环 foreach，只支持 GNU Make ，其它平台的make ，可以用shell 中的循环来实现
#可以在循环中逐个的修改值

TARGET:=a b c d
FILE:=$(foreach v, $(TARGET),$v.txt)

all:
	#echo $(TARGET)
	#echo $(foreach v, $(TARGET),$v)
	#touch $(TARGET)
	#touch $(foreach v, $(TARGET),$v.txt)
	#mkdir $(foreach v, $(TARGET),$v_txt)
	#echo $(FILE)

	for v in $(TARGET);\
		do touch $$v.txt;\
	done;\

	$(shell for v in $(TARGET); do touch $$v-txt;done)


clean:
	$(RM) -rf $(TARGET) *txt
```



## 13. makefile 中自定义函数的实现和调用

+ 自定义函数不是真正的函数，本质上是多行命令放在了目标外
+ 可以传递参数
+ 没有返回值

```makefile
A := 123

define FUNC1
	echo func
	echo $(0) $(1) $(2)
endef

define FUNC2
	return 123
endef

define FUNC3
	echo $(shell ls)
endef

all:
	$(call FUNC1, $(A), asd)
	$(call FUNC2)
	$(call FUNC3)
```



## 14. make install 的实现

### 14.1 上部

make   1
make install   2 3 4
make clean  5

1 将源文件编译成二进制可执行文件(包括各种库文件)
2 创建目录，将可执行文件拷贝到指定目录(安装目录)
3 加全局可执行的路径
4 加全局的启停脚本
5 重置编辑环境，删除无关文件

#### 006_main.cpp

```c++
#include<iostream>
#include<unistd.h>
using namespace std;

int main(){

    int i=0;
    while (true){
        i++;
        cout<<"006-main-running-"<<i<<endl;
        sleep(1);
    }

    return 0;
}
```

#### makefile

```makefile
TARGET:=006_main
OBJ:=$(TARGET).o

CC:=g++

PATH:=/tmp/006_main/
BIN:=/usr/local/bin/

$(TARGET):$(OBJ)

install:$(TARGET)
	if [ -d $(PATH) ];\
		then echo $(PATH) exist; \
	else \
	  	/bin/mkdir $(PATH);\
	  	/bin/cp $(TARGET) $(PATH);\
  		/bin/ln -sv $(PATH)$(TARGET) $(BIN);\
  	fi;

clean:
	$(RM) $(TARGET) $(OBJ)
	$(RM) -rf $(PATH)


.PHONY:clean install
```

### 14.2 下部

[Code](https://github.com/niu0217/AssaultPlan/tree/main/MakeFile/source/makeInstall%E7%9A%84%E5%AE%9E%E7%8E%B0%E4%B8%8B%E9%83%A8)

#### 006_main.cpp

```c++
#include<iostream>
#include<unistd.h>
using namespace std;

int main(){

    int i=0;
    while (true){
        i++;
        cout<<"006-main-running-"<<i<<endl;
        sleep(1);
    }

    return 0;
}
```

#### makefile

```makefile

TARGET:=006_main
OBJ:=$(TARGET).o

CC:=g++

PATHS:=/tmp/006_main/
BIN:=/usr/local/bin/


START_SH:=$(TARGET)_start
STOP_SH:=$(TARGET)_stop
LOG:=$(PATHS)$(TARGET).log


$(TARGET):$(OBJ)


install:$(TARGET)
	if [ -d $(PATHS) ];\
		then echo $(PATHS) exist; \
	else \
	  	mkdir $(PATHS);\
	  	cp $(TARGET) $(PATHS);\
  		ln -sv $(PATHS)$(TARGET) $(BIN);\
  		touch $(LOG);\
  		chmod a+rwx $(LOG);\
  		echo "$(TARGET)>$(LOG) & echo $(TARGET) running...">$(PATHS)$(START_SH);\
  		echo "killall $(TARGET)">$(PATHS)$(STOP_SH);\
  		chmod a+x $(PATHS)$(START_SH);\
  		chmod a+x $(PATHS)$(STOP_SH);\
  		ln -sv $(PATHS)$(START_SH) $(BIN);\
  		ln -sv $(PATHS)$(STOP_SH) $(BIN);\
  	fi;

clean:
	$(RM) $(TARGET) $(OBJ) $(BIN)$(TARGET) $(BIN)$(START_SH) $(BIN)$(STOP_SH)
	$(RM) -rf $(PATHS)

.PHONY:clean install
```

