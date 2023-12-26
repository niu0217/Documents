# C++中的extern

## 1. 问题

## 2. C中的extern

在C语言中，`extern`是一个关键字，主要用于声明变量或函数的作用域和链接属性。

1. **声明外部变量**： 当你在一个源文件中使用 `extern` 关键字声明一个变量时，你是在告诉编译器这个变量的定义存在于其他的源文件中。这允许你在多个源文件中共享和访问同一个全局变量。 

   例如，在一个源文件（file1.c）中定义了一个全局变量：

   ```c
   // file1.c
   int sharedVariable = 0;
   ```

   然后在另一个源文件（file2.c）中通过 `extern` 声明并访问这个变量：

   ```c
   // file2.c
   extern int sharedVariable;
   
   void someFunction() {
       sharedVariable = 10;
   }
   ```

2. **声明外部函数**： 类似于外部变量，你也可以使用 `extern` 关键字声明一个外部函数，表示该函数的定义在其他源文件中。对于函数来说，通常并不需要显式地使用 `extern`，因为函数默认就是外部链接的。

   例如，在一个源文件（file1.c）中定义了一个函数：

   ```c
   // file1.c
   int add(int a, int b) {
       return a + b;
   }
   ```

   然后在另一个源文件（file2.c）中通过 `extern` 声明并调用这个函数：

   ```c
   // file2.c
   extern int add(int a, int b);
   
   void someOtherFunction() {
       int result = add(5, 7);
       printf("The result is %d\n", result);
   }
   ```

注意，`extern` 关键字主要用于解决不同源文件之间的链接问题，使得它们可以共享全局变量和函数。在单个源文件中，全局变量和函数默认就是外部链接的，因此通常不需要显式地使用 `extern`。但是，在某些情况下，比如在头文件中声明全局变量或函数以供多个源文件使用时，`extern` 关键字是必要的。

## 3. 在头文件中使用extern

在头文件（通常以 `.h` 或 `.hpp` 为扩展名）中使用 `extern` 关键字的主要目的是为了让多个源文件（`.c` 或 `.cpp`）共享全局变量或函数的声明。

以下是在头文件中使用 `extern` 的一些关键点：

1. **共享声明**： 当你在头文件中使用 `extern` 声明一个全局变量或函数时，你实际上是创建了一个该变量或函数的引用。当其他源文件包含这个头文件时，它们就可以访问到这个共享的声明。
2. **避免重复定义**： 如果不使用 `extern`，每个包含该头文件的源文件都会生成变量或函数的定义，这会导致链接时出现“多重定义”错误。通过在头文件中使用 `extern`，你可以确保只有在一个源文件中定义变量或函数，而在其他源文件中只是声明它们。
3. **链接过程中的解析**： 在编译过程中，编译器会处理源文件中的代码，并生成目标文件。在链接阶段，链接器会将所有目标文件合并成一个可执行文件，并解决所有外部符号（即使用 `extern` 声明的变量和函数）的引用。通过在头文件中使用 `extern`，你可以告诉链接器这些变量和函数的定义存在于其他目标文件中。

以下是一个例子：

```c
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H

extern int sharedVariable;
extern void someFunction(void);

#endif // MYHEADER_H
```

在这个头文件中，`sharedVariable` 和 `someFunction` 被声明为外部的。现在，当你在其他源文件中包含这个头文件并使用这些变量或函数时，编译器知道它们的定义在其他地方，并且链接器会在链接阶段找到并解析这些定义。

```c
// file1.c
int sharedVariable = 0;

void someFunction() {
    // ...
}

// file2.c
#include "myheader.h"

void anotherFunction() {
    sharedVariable++;
    someFunction();
}
```

在这个例子中，`file2.c` 可以通过包含 `myheader.h` 来访问 `sharedVariable` 和 `someFunction()`，而不需要知道它们的具体实现。链接器会在链接 `file1.o` 和 `file2.o` 时解析这些外部引用。

## 4. extern "C"

`extern "C"` 是 C++ 中的一个链接指定符，用于解决 C 和 C++ 语言之间的兼容性问题。在 C++ 中，函数和变量的名称会经过名称修饰（name mangling），使得编译器可以生成唯一的符号来区分重载函数、模板实例等。然而，C 语言并不支持名称修饰，因此 C 和 C++ 编译器之间无法直接识别彼此生成的函数和变量。

`extern "C"` 的作用主要有以下几点：

1. **保持 C 兼容性**： 当你在 C++ 中使用 `extern "C"` 来声明一个函数或变量时，你告诉编译器按照 C 语言的方式处理这个函数或变量的名称，即不进行名称修饰。这使得 C++ 编译器生成的代码可以被 C 编译器识别和使用。

   例如，在一个 C++ 源文件中，你可以这样声明一个与 C 兼容的函数：

   ```c++
   extern "C" {
       int myFunction(int a, int b);
   }
   ```

2. **链接 C 库**： `extern "C"` 常用于在 C++ 程序中调用 C 语言编写的库函数。通过将函数声明放在 `extern "C"` 块中，你可以确保 C++ 编译器正确地处理这些函数的名称，从而能够成功链接到 C 库。

   例如，如果你正在使用一个名为 `my_c_library` 的 C 库，该库提供了一个名为 `add_numbers` 的函数，你可以在 C++ 程序中这样声明和使用它：

   ```c++
   extern "C" {
       int add_numbers(int a, int b);
   }
   
   int main() {
       int result = add_numbers(5, 7);
       std::cout << "The result is " << result << std::endl;
       return 0;
   }
   ```

3. **混合 C 和 C++ 代码**： 当你的项目同时包含 C 和 C++ 源文件时，你可以使用 `extern "C"` 来确保 C 和 C++ 代码之间的互操作性。在这种情况下，你通常需要在 C++ 源文件中包含 C 头文件，并使用 `extern "C"` 来声明那些需要在 C 和 C++ 之间共享的函数。 

   例如，假设你有一个名为 `my_c_code.h` 的 C 头文件，其中定义了一个函数 `calculate_sum`，你可以在 C++ 源文件中这样使用它：

   ```c++
   #ifdef __cplusplus
   extern "C" {
   #endif
   
   #include "my_c_code.h"
   
   #ifdef __cplusplus
   }
   #endif
   
   int main() {
       int result = calculate_sum(5, 7);
       std::cout << "The result is " << result << std::endl;
       return 0;
   }
   ```

通过使用 `extern "C"`，C++ 程序可以方便地调用 C 函数和使用 C 库，同时也能够在 C 和 C++ 代码之间实现无缝集成。