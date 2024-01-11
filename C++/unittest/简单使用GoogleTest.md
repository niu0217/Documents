# 简单使用GoogleTest

## 1. 必备知识

### 1.1 必读文档

[GoogleTestPrimer.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/unittest/GoogleTestPrimer.md)

[googletestreadme.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/unittest/googletestreadme.md)

[GoogleTest.md](https://github.com/niu0217/Documents/blob/main/C%2B%2B/unittest/GoogleTest.md)

### 1.2 如何使用gtest

- 断言
  分ASSERT_XXX 和 EXPECT_XXX两类.
  区别:
  如果ASSERT_XXX 测试结果不通过,后面的测试就不会执行了.
  如果EXPECT_XXX 测试结果不通过,后面的测试会接着执行.
  布尔断言：单参断言
  ASSERT_TRUE、ASSERT_FALSE、EXPECT_TRUE、EXPECT_FALSE
  数值断言：双参
  ASSERT_EQ、ASSERT_NE、ASSERT_LT、ASSERT_LE、ASSERT_GT、ASSERT_GE
  EXPECT_EQ、EXPECT_NE、EXPECT_LT、EXPECT_LE、EXPECT_GT、EXPECT_GE
  字符串断言
  ASSERT_STREQ、ASSERT_STRCASEEQ
- TEST(test_suite_name,test_name)
  一个TEST()算是一个测试case.
  TEST(x,y)展开为x_y_TEST()这样的函数
  比如测试add()函数,我们可以考虑多种测试情况:和为负数,和为正数,极限值测试.

## 2. 使用

### 2.1 以静态库的方式

参考资料：https://www.cnblogs.com/jlh-/p/16985906.html

#### 2.1.1 步骤一

假设我们把所有的东西都保存在文件夹GoogleTest中，初始时为空。

将 GoogleTest 构建为独立项目时，典型的工作流程从:

```bash
git clone https://github.com/google/googletest.git -b v1.14.0
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
```

上面的命令默认还包含GoogleMock。 因此，如果您只想构建 GoogleTest，则应该将最后一个命令替换为:

```bash
cmake .. -DBUILD_GMOCK=OFF
```

如果您使用的是 `*nix系统`，您现在应该在当前目录中看到一个 Makefile。 只需输入 make 即可构建 GoogleTest。 如果您是系统管理员，则只需安装 GoogleTest 即可。

```bash
make
sudo make install    # Install in /usr/local/ by default
```

如果您使用 Windows 并安装了 Visual Studio，则会创建一个 `gtest.sln` 文件和几个 `.vcproj` 文件。 然后您可以使用 Visual Studio 构建它们。

在安装了 Xcode 的 Mac OS X 上，将生成 `.xcodeproj` 文件。

执行完这一步之后，我们的文件结构：

```bash
ubuntu@niu0217:~/Dev/GoogleTest/googletest$ ls -l
total 64
drwxrwxr-x 7 ubuntu ubuntu 4096 Jan 11 16:40 build
-rw-rw-r-- 1 ubuntu ubuntu 6488 Jan 11 16:37 BUILD.bazel
drwxrwxr-x 2 ubuntu ubuntu 4096 Jan 11 16:37 ci
-rw-rw-r-- 1 ubuntu ubuntu  819 Jan 11 16:37 CMakeLists.txt
-rw-rw-r-- 1 ubuntu ubuntu 5688 Jan 11 16:37 CONTRIBUTING.md
-rw-rw-r-- 1 ubuntu ubuntu 2261 Jan 11 16:37 CONTRIBUTORS
drwxrwxr-x 7 ubuntu ubuntu 4096 Jan 11 16:37 docs
drwxrwxr-x 7 ubuntu ubuntu 4096 Jan 11 16:37 googlemock
drwxrwxr-x 8 ubuntu ubuntu 4096 Jan 11 16:37 googletest
-rw-rw-r-- 1 ubuntu ubuntu 1124 Jan 11 16:37 googletest_deps.bzl
-rw-rw-r-- 1 ubuntu ubuntu 1475 Jan 11 16:37 LICENSE
-rw-rw-r-- 1 ubuntu ubuntu 5814 Jan 11 16:37 README.md
-rw-rw-r-- 1 ubuntu ubuntu 1159 Jan 11 16:37 WORKSPACE
```

重要的文件:

```bash
ubuntu@niu0217:~/Dev/GoogleTest/googletest/build/lib$ ls -l
total 3616
-rw-rw-r-- 1 ubuntu ubuntu  892680 Jan 11 16:40 libgmock.a
-rw-rw-r-- 1 ubuntu ubuntu    4636 Jan 11 16:40 libgmock_main.a
-rw-rw-r-- 1 ubuntu ubuntu 2792798 Jan 11 16:40 libgtest.a
-rw-rw-r-- 1 ubuntu ubuntu    4356 Jan 11 16:40 libgtest_main.a
ubuntu@niu0217:~/Dev/GoogleTest/googletest/build/lib$
```

#### 2.1.2 步骤二

新建一个项目，然后把步骤一中的`build/lib`文件夹拷贝过来，文件结构如下：

```
ubuntu@niu0217:~/Dev/TestGoogleTest$ tree
.
├── lib
│   ├── libgmock.a
│   ├── libgmock_main.a
│   ├── libgtest.a
│   └── libgtest_main.a
├── main.cpp
└── makefile

1 directory, 6 files
ubuntu@niu0217:~/Dev/TestGoogleTest$
```

文件内容：

```c++
//main.cpp

#include <gtest/gtest.h>
#include <iostream>
#include <string>

int add(int a, int b)
{
	return a + b;
}

TEST(fun, add_a)
{
	EXPECT_EQ(-3, add(-2,-1));
	EXPECT_EQ(-2, add(1,-3));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
```

```makefile
# makefile

CXX = g++
CXXFLAGS = -std=c++14 -Wall -o

SRC = main.cpp
TARGET = main

LIBS = -lgtest -lpthread
LIBPATH = -L ./lib

all:
	$(CXX) $(CXXFLAGS) $(TARGET) $(SRC) $(LIBS) $(LIBPATH)

clean:
	rm $(TARGET)
```

执行：

```bash
ubuntu@niu0217:~/Dev/TestGoogleTest$ make
g++ -std=c++14 -Wall -o main main.cpp -lgtest -lpthread -L ./lib
ubuntu@niu0217:~/Dev/TestGoogleTest$ ./main
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from fun
[ RUN      ] fun.add_a
[       OK ] fun.add_a (0 ms)
[----------] 1 test from fun (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
ubuntu@niu0217:~/Dev/TestGoogleTest$
```

#### 2.1.3 步骤三

更换步骤二的main.cpp文件，查看结果：

```c++
//main.cpp

#include <gtest/gtest.h>
#include <iostream>
#include <string>

int add(int a, int b)
{
	return a + b;
}

TEST(add, negative)
{
	EXPECT_EQ(-3, add(-2,-1));
	EXPECT_EQ(-2, add(1,-3));
}

TEST(add, positive)
{
	EXPECT_EQ(1, add(2,-1));
	EXPECT_EQ(2, add(-1,3));
}

TEST(add, limit)
{
    int a = 0x7fffffff + 1;
    std::cout<<"a = "<<a<<"\n";
	EXPECT_EQ(a, add(0x7fffffff,1));
	EXPECT_EQ(0, add(0xffffffff,1));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
	  return RUN_ALL_TESTS();
}
```

执行结果：

```bash
ubuntu@niu0217:~/Dev/TestGoogleTest$ make
g++ -std=c++14 -Wall -o main main.cpp -lgtest -lpthread -L ./lib
main.cpp: In member function ‘virtual void add_limit_Test::TestBody()’:
main.cpp:24:24: warning: integer overflow in expression of type ‘int’ results in ‘-2147483648’ [-Woverflow]
   24 |     int a = 0x7fffffff + 1;
      |             ~~~~~~~~~~~^~~
ubuntu@niu0217:~/Dev/TestGoogleTest$ ./main
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from add
[ RUN      ] add.negative
[       OK ] add.negative (0 ms)
[ RUN      ] add.positive
[       OK ] add.positive (0 ms)
[ RUN      ] add.limit
a = -2147483648
[       OK ] add.limit (0 ms)
[----------] 3 tests from add (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
ubuntu@niu0217:~/Dev/TestGoogleTest$
```

#### 2.1.4 步骤四

修改main.cpp文件

```c++
//main.cpp

#include <gtest/gtest.h>
#include <iostream>
#include <string>

int add(int a, int b)
{
	return a + b;
}

TEST(add, negative)
{
	EXPECT_EQ(-3, add(-2,-1));
	EXPECT_EQ(-2, add(1,-3));
}

TEST(add, positive)
{
	EXPECT_EQ(1, add(2,-1));
	EXPECT_EQ(2, add(-1,3));
}

TEST(add, limit)
{
    int a = 0x7fffffff + 1;
    std::cout<<"a = "<<a<<"\n";
	EXPECT_EQ(a, add(0x7fffffff,1));
	EXPECT_EQ(0, add(0xffffffff,1));
}

class FooTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FooTest() {
     // You can do set-up work for each test here.
  }

  ~FooTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }
  static void SetUpTestSuite() {
    std::cout<<"===================run before first case..."<<std::endl;
  }

  static void TearDownTestSuite() {
    std::cout<<"===================run after last case..."<<std::endl;
  }
  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    std::cout<<" =========================SetUp() \n";
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
    std::cout<<" =========================TearDown() \n";
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

TEST_F(FooTest,test_a)
{
  EXPECT_EQ(2, add(0x7fffffff,1));
}

TEST_F(FooTest,test_b)
{
  EXPECT_EQ(1, add(0,1));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
	  return RUN_ALL_TESTS();
}
```

执行结果：

```bash
ubuntu@niu0217:~/Dev/TestGoogleTest$ make
g++ -std=c++14 -Wall -o main main.cpp -lgtest -lpthread -L ./lib
main.cpp: In member function ‘virtual void add_limit_Test::TestBody()’:
main.cpp:24:24: warning: integer overflow in expression of type ‘int’ results in ‘-2147483648’ [-Woverflow]
   24 |     int a = 0x7fffffff + 1;
      |             ~~~~~~~~~~~^~~
.ubuntu@niu0217:~/Dev/TestGoogleTest$ ./main
[==========] Running 5 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from add
[ RUN      ] add.negative
[       OK ] add.negative (0 ms)
[ RUN      ] add.positive
[       OK ] add.positive (0 ms)
[ RUN      ] add.limit
a = -2147483648
[       OK ] add.limit (0 ms)
[----------] 3 tests from add (0 ms total)

[----------] 2 tests from FooTest
===================run before first case...
[ RUN      ] FooTest.test_a
 =========================SetUp()
main.cpp:70: Failure
Expected equality of these values:
  2
  add(0x7fffffff,1)
    Which is: -2147483648

 =========================TearDown()
[  FAILED  ] FooTest.test_a (0 ms)
[ RUN      ] FooTest.test_b
 =========================SetUp()
 =========================TearDown()
[       OK ] FooTest.test_b (0 ms)
===================run after last case...
[----------] 2 tests from FooTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 4 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] FooTest.test_a

 1 FAILED TEST
ubuntu@niu0217:~/Dev/TestGoogleTest$
```



