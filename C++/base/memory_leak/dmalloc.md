# dmalloc

## [官网](https://dmalloc.com/docs/dmalloc.html)

## 2. Description of features and how to get started.

### 2.1 How to Install the Library

要配置、编译和安装该库，请仔细遵循以下步骤。

1. 从 http://dmalloc.com/ 下载该库的最新版本。

2. 发布文件具有“.tgz”文件扩展名，这意味着它们是经过 tar 压缩的文件目录。 您需要 ungzip，然后将发布文件解压到源工作目录中。 您可能需要将文件重命名为“.tar.gz”才能让一些旧的 zip 程序正确处理该文件。

3. 您可能需要编辑或至少查看“settings.dist”中的设置以调整库的特定功能。 “configure”脚本会将此文件复制到“settings.h”，您应该在其中添加每个架构的设置。

4. 键入 `sh ./configure` 以配置库。 您可能需要首先检查“config.help”文件以获取有关配置的一些信息。 如果您不希望 Makefile 构建 C++ 版本的 dmalloc，您可能需要使用 `--disable-cxx` 选项。 您可能需要使用 `--enable-threads` 选项来构建 dmalloc 的线程版本。 您可能需要使用 `--enable-shlib` 选项来构建 dmalloc 库的共享版本。 `sh ./configure --help` 列出了可配置的选项。 配置应该自动生成“Makefile”和配置文件。

5. 您可能需要检查configure创建的“Makefile”和“conf.h”文件，以确保它正确完成其工作。

6. 您可能需要调整“settings.h”文件中的设置，以将库调整为本地架构。 如果您使用 pthreads 或其他线程库，此文件包含相关设置。 请参阅将库与线程包一起使用部分。 “configure”脚本从“settings.dist”文件创建了该文件。 对这些设置的任何永久更改都应该对“settings.dist”文件进行。 然后，您可以运行“config.status”来重新创建“settings.h”文件。

7. `DMALLOC_SIZE` 变量在“dmalloc.h.2”中自动配置，但它可能无法为所有系统生成正确的设置。 当您编译 malloc 例程的大小参数时，您可能必须更改此文件中的定义才能停止抱怨。 请对此发表评论。

8. 输入 make 应该足以构建“libdmalloc.a”和“dmalloc”程序。 如果不起作用，请查看 contrib 目录中是否有关于您的系统类型的注释。 如果没有，并且您解决了问题，请给我发送一些注释，以便未来的用户可以从您的经验中受益。

   注意：在编译某些“return.h”程序集宏时，您可能会遇到一些错误，这些宏试图确定调用者地址以用于记录目的。 请参阅移植库的重要问题部分。 您可能需要首先尝试禁用任何编译器优化标志。 如果这不起作用，那么您可能需要禁用“settings.h”文件中的“USE_RETURN_MACROS”变量。

   注意：该代码依赖于 ANSI-C 编译器。 如果配置脚本给出“警告”，表明您没有 ANSI-C 编译器，您仍然可以向编译器添加某种选项以使其成为 ANSI。 如果有这样的选项，请将其发送给作者，以便将其添加到配置脚本中。

9. 如果您使用线程并且没有在配置中添加 `--enable-threads` 参数，则输入 makethreads 应该足以构建“libdmallocth.a”，这是库的线程版本。 这可能有效也可能无效，具体取决于配置脚本检测本地线程功能的能力。 请随时向我发送有关改进的邮件。
   有关线程程序的库操作的更多信息，请参阅手册中有关线程的部分。 请参阅将库与线程包一起使用部分。

10. 如果您安装了 C++ 编译器，则该库应该自动构建“libdmallocxx.a”，这是该库的 C++ 版本。 如果没有自动完成，您可以通过键入 `make cxx` 来构建它。 您应该将该库链接到您的 C++ 程序中，而不是“libdmalloc.a”。 请参阅“dmallocc.cc”C++ 文件，其中包含重载 new、new[]、delete 和 delete[] C++ 运算符的基本代码。 对于最低限度的 C++ 支持，我深表歉意。 我仍然生活在一个以 C 语言为主的世界里。 任何在不牺牲可移植性的情况下改进此界面的帮助将不胜感激。

11. 键入 `make light` 应该通过一组 light 试验来构建并运行“dmalloc_t”测试程序。 默认情况下，这将执行“dmalloc_t”5 次——每次都会以非常随机的方式执行 10,000 个 malloc 操作。 Anal folks 可以通过打字来提高赌注。 使用 `dmalloc_t --usage` 获取所有“dmalloc_t”选项的列表。

12. 键入 `make install` 应将“libdmalloc.a”库安装在“`/usr/local/lib`”中，将“dmalloc.h”包含文件安装在“`/usr/local/include`”中，并将“dmalloc”实用程序安装在“/usr”中 /本地/bin'。 您可能还需要输入 make installth 将线程库安装到位和/或 make installcc 将 C++ 库安装到位。
    您可能已指定“--prefix=PATH”选项进行配置，在这种情况下，“/usr/local”将被替换为“PATH”。

### 2.2 Getting Started with the Library

本节应该让您快速了解如何开始。 基本上，您需要执行以下操作才能使用该库：

1. 从 http://dmalloc.com/ 下载最新版本的库。

2. 运行 `./configure` 来配置库。 按照有关如何配置、制作和安装库的安装说明进行操作（即键入：make install）。 请参阅如何安装库部分。

3. 运行 `./make install` 在您的系统上安装该库。

4. 您需要确保上面的库配置和构建过程能够找到 on_exit 函数、atexit 函数之一，或者具有编译器析构函数支持。 如果这些功能或支持之一可用，那么 dmalloc 库应该能够在程序退出时自动关闭。 这会导致内存统计信息和未释放的信息转储到日志文件中。 但是，如果您的系统没有上述任何一个，那么您需要在程序退出之前自己调用 dmalloc_shutdown。

5. 要使 dmalloc 实用程序正常工作，您需要将 dmalloc 的别名添加到 shell 的运行时配置文件（如果支持）。 这个想法是让 shell 捕获 dmalloc 程序的输出并调整环境。
   将别名添加到 shell 配置文件后，您需要注销并重新登录才能生效，或者您可以直接在命令行上执行下面相应的命令。 设置别名后，如果您进入 dmalloc 运行时并看到其中包含 DMALLOC_OPTIONS 的任何输出，则说明别名未生效。

   Bash、ksh 和 zsh (http://www.zsh.org/) 用户应分别将以下内容添加到其“.bashrc”、“.profile”或“.zshrc”文件中（注意 bourne 的 -b 选项） 外壳输出）：

   ```bash
   function dmalloc { eval `command dmalloc -b $*`; }
   ```

   如果您的 shell 不支持命令功能，请尝试：

   ```bash
   function dmalloc { eval `\dmalloc -b $*`; }
   ```

   或使用 dmalloc 二进制文件安装位置的完整路径：

   ```bash
   function dmalloc { eval `/usr/local/bin/dmalloc -b $*`; }
   ```

   如果您仍在使用 csh 或 tcsh，则应将以下内容添加到“.cshrc”文件中（注意 c-shell 输出的 -C 选项）：

   ```bash
   alias dmalloc 'eval `\dmalloc -C \!*`'
   ```

   如果您使用 rc shell，则应将以下内容添加到“.rcrc”文件中（注意 rc-shell 输出的 -R 选项）：

   ```bash
   fn dmalloc {eval `{/usr/local/bin/dmalloc $*}}
   ```

6. 尽管没有必要，您可能希望在 C 文件中包含“dmalloc.h”并重新编译。 这将允许库报告产生问题的调用的文件/行号。 请参阅提供文件和行信息的宏部分。 它应该插入到包含文件的底部，以免与其他包含文件发生冲突。 您可能还想 ifdef 它并使用 `cc -DDMALLOC` 进行编译...：

   ```c
   /* other includes above ^^^ */
   
   #ifdef DMALLOC
   #include "dmalloc.h"
   #endif
   ```

7. 另一个可选任务是使用带有 DMALLOC_FUNC_CHECK 编译标志的“dmalloc.h”来编译所有源代码。 这将允许库检查许多常见字符串和实用程序例程的所有参数。 请参阅函数参数检查部分。

   ```makefile
   cc -DDMALLOC -DDMALLOC_FUNC_CHECK file.c
   ```

8. 将 dmalloc 库链接到您的程序中。 dmalloc 库可能应该放置在库列表的末尾或末尾附近。

9. 通过键入 `dmalloc -l logfile -i 100 low`（例如）来启用调试功能。 您不应看到 dmalloc 实用程序打印的任何消息（请参阅下面的注释）。 这会：

   + 将 malloc 日志文件名称设置为“logfile”（-l logfile）。 对于更改目录的程序，您可能需要指定日志文件的完整路径。
   + 让库每 100 次迭代检查一次 (-i 100)。 这控制了程序的运行速度。 数字越大，对堆的检查越少，因此运行速度会更快。 数字越低，就越有可能发现内存问题。
   + 启用许多调试功能（低）。 您还可以尝试运行时进行最少的检查，或尝试中或高的运行时进行更广泛的堆验证。
   + 默认情况下，低、中和高值启用错误中止标记，这将导致库中止并通常在看到错误时立即转储核心。 请参阅“在出现错误时生成核心文件”部分。 您可以通过输入 `dmalloc -m error-abort`（-m 表示减号）来禁用此功能，以删除错误中止标记，您的程序将仅记录错误并继续。

   `dmalloc --usage` 将为 dmalloc 程序提供详细的使用信息。 请参阅 Dmalloc 实用程序部分。

10. 您可能还想在主目录中将“dmallocrc”文件安装为“.dmallocrc”。 这允许您添加自己的调试令牌组合。 请参阅运行时配置文件的格式部分。

    注意： dmalloc 实用程序的输出应由 shell 捕获。 如果您看到一堆包含字符串 DMALLOC_OPTIONS 的内容，那么您应该在上面创建的别名不起作用，并且未设置环境变量。 确保您已注销并重新登录以使别名生效。

11. 运行您的程序，检查应由 dmalloc_shutdown 创建的日志文件，并使用其信息来帮助调试您的程序。

### 2.3 Basic Description of Terms and Functions

#### 2.3.1 General memory terms and concepts.

任何程序都可以分为两个逻辑部分：文本和数据。 文本是机器可读格式的实际程序代码，数据是文本执行时所操作的信息。 数据根据存储位置又可以分为 3 个逻辑部分：静态、堆栈和堆。

静态数据是其存储空间被编译到程序中的信息。

```c
/* global variables are allocated as static data */
int numbers[10];

main()
{
   …
}
```

Stack data is data allocated at runtime to hold information used inside of functions. This data is managed by the system in the space called stack space.

```c
void foo()
{
   /* this local variable is stored on the stack */
   float total;
   …
}

main()
{
   foo();
}
```

Heap data is also allocated at runtime and provides a programmer with dynamic memory capabilities.

```c
 	
main()
{
   /* the address is stored on the stack */
   char * string;
   …

   /*
    * Allocate a string of 10 bytes on the heap.  Store the
    * address in string which is on the stack.
    */
   string = (char *)malloc(10);
   …

   /* de-allocate the heap memory now that we're done with it */
   (void)free(string);
   …
}

```

It is the heap data that is managed by this library.

尽管上面是如何使用 malloc 和 free 命令的示例，但这并不是说明为什么使用堆进行运行时存储有用的好示例。

考虑一下：您编写一个程序，将文件读入内存，对其进行处理并显示结果。 您想要处理任意大小的文件（从 10 字节到 1.2 兆字节及更多）。 然而，一个问题是整个文件必须同时位于内存中才能进行计算。 当您可能只读取 10 字节文件时，您不希望分配 1.2 MB，因为这会浪费系统资源。 此外，您还担心您的程序可能必须处理超过 1.2 MB 的文件。

解决方案：首先检查文件的大小，然后使用堆分配例程获取足够的存储空间以将整个文件读入内存。 该程序将仅使用该作业所需的系统资源，并且将保证您的程序可以处理任何大小的文件。

#### 2.3.2  Functionality supported by all malloc libs.

所有 malloc 库都支持 4 个基本内存分配命令。 其中包括 malloc、calloc、realloc 和 free。 有关其功能的更多信息，请检查系统的手册页 - 在 unix 中，执行 `man 3 malloc`。

- Function: `void *malloc( unsigned int size )`

  Usage: `pnt = (type *)malloc(size)`

  The malloc routine is the basic memory allocation routine. It allocates an area of `size` bytes. It will return a pointer to the space requested.

- Function: `void *calloc( unsigned int number, unsigned intsize )`

  Usage: `pnt = (type *)calloc(number, size)`

  The calloc routine allocates a certain `number` of items, each of `size` bytes, and returns a pointer to the space. It is appropriate to pass in a `sizeof(type)` value as the size argument.Also, calloc nulls the space that it returns, assuring that the memory is all zeros.

- Function: `void *realloc( void *old_pnt, unsigned int new_size )`

  Usage: `new_pnt = (type *)realloc(old_pnt, new_size)`

  The realloc function expands or shrinks the memory allocation in `old_pnt` to `new_size` number of bytes. Realloc copies as much of the information from `old_pnt` as it can into the `new_pnt` space it returns, up to `new_size` bytes. If there is a problem allocating this memory, 0L will be returned.If the `old_pnt` is 0L then realloc will do the equivalent of a `malloc(new_size)`. If `new_size` is 0 and `old_pnt` is not 0L, then it will do the equivalent of `free(old_pnt)` and will return 0L.

- Function: `void *free( void *pnt )`

  Usage: `free(pnt)`

  The free routine releases allocation in `pnt` which was returned by malloc, calloc, or realloc back to the heap. This allows other parts of the program to re-use memory that is not needed anymore. It guarantees that the process does not grow too big and swallow a large portion of the system resources.

警告：有一个很常见的神话，即 malloc 库返回的所有空间都已被清除。 只有 calloc 例程会将其返回的内存空间清零。

### 2.4 General Features of the Library

此调试 malloc 库中提供的调试功能可以分为几个基本类别：

+ file and line number information

  + 好的调试器的好处之一是它能够提供有问题的代码段的文件和行号。 该库尝试在 C 预处理器 cpp 的帮助下提供此功能。 请参阅提供文件和行信息的宏部分。

+ return-address information

  + 为了调试从外部源（即那些无法使用分配宏的文件）对库的调用，提供了一些工具来提供调用者的地址。 这个地址在调试器的帮助下，可以帮助你定位问题的根源。 请参阅获取主叫地址信息部分。

+ fence-post (i.e. bounds) checking

  + *Fence-post* memory是紧邻内存分配上方或下方的区域。 编写访问分配之上或之下的代码太容易了——尤其是在处理数组或字符串时。 库可以在每个分配周围的区域中写入特殊值，以便它会注意到这些区域何时被覆盖。 请参阅诊断 Fence-Post 覆盖内存部分。

    注意：库无法注意到程序何时从这些区域读取，只能注意到何时写入值。 此外，栅栏后检查将增加程序分配的内存量。

+ heap-constancy verification

  + library的管理相当复杂。 如果任何堆维护信息被损坏，程序将崩溃或给出不可预测的结果。

    通过启用堆一致性检查，库将运行其管理结构以确保一切正常。 这意味着可以更快地发现问题并更好地诊断问题。

    当然，这样做的缺点是library通常需要相当长的时间才能完成这项工作。 仅在开发和调试会话期间才适合启用此功能。

    注意：如果堆管理结构被正确地（或不正确地，如果您愿意的话）覆盖，堆检查例程不能保证测试不会导致分段错误。 换句话说，测试将验证一切正常，但可能不会以优雅的方式告知用户问题。

+ logging statistics

  + 最初开发 debug malloc 库的原因之一是跟踪程序的内存使用情况，特别是定位内存泄漏，即分配的内存永远不会被释放的地方。 请参阅“追踪未释放内存”部分。

    该库具有许多日志记录功能，可以跟踪未释放的内存指针以及运行时内存使用情况、内存事务、管理操作和最终统计信息。

+ examining freed memory

  + 当程序释放内存指针但又错误地再次使用它时，会发生另一个常见问题。 这可能会导致神秘的崩溃和无法解释的问题。

    为了解决这个问题，库可以在释放内存块后将特殊值写入该内存块中。 这有两个目的：它将确保程序在尝试再次访问该区域时将获得垃圾数据，并且将允许库稍后验证该区域是否有覆盖迹象。

如果上述任何调试功能检测到错误，该库将尝试恢复。 如果启用日志记录，则会记录错误并包含尽可能多的信息。

库显示的错误消息旨在为开发人员提供最多的信息。 如果错误消息无法理解，那么它很可能只是试图表明堆的一部分已损坏。

该库可以配置为在检测到错误时立即退出并转储核心文件或内存映像。 可以使用调试器进行检查以确定问题的根源。 该库可以在转储核心后停止或继续运行。 请参阅“在出现错误时生成核心文件”部分。

注意：如果库发现您的系统例程存在问题，请不要感到惊讶。 我花了几个小时才最终得出结论：SunOS 4.1 版本中包含的本地时间调用覆盖了其栅栏标记之一。

### 2.5 How the Library Checks Your Program

这是该库的较新部分之一，意味着它不完整。 如果您有任何疑问或问题希望在这里得到处理，请告诉我。

dmalloc 库用它自己的版本替换了通常在系统库中找到的堆库调用。 例如，当您调用 malloc 时，您正在调用 dmalloc 版本的内存分配函数。 当您使用这些函数分配内存时，dmalloc 库会跟踪有关指针的许多调试信息，包括：分配的位置、到底请求了多少内存、何时进行调用等。这些信息可以 然后在释放或重新分配指针时进行验证，并且可以记录任何错误的详细信息。

每当您重新分配或释放内存地址时，dmalloc 库都会对指针执行多次检查，以确保其有效且未被损坏。 您可以配置库以执行其他检查，例如检测到的栅栏柱写入。 该库还可以配置为在分配内存时用非零覆盖内存（仅当未调用 calloc 时），并在释放指针时擦除内存。

除了每个指针检查之外，您还可以配置库以执行完整的堆检查。 这些完整的检查验证所有内部堆结构，并包括遍历所有已知的已分配指针以依次验证每个指针。 您需要这种级别的检查来查找程序中已损坏但暂时不会被释放的随机指针。 要打开这些检查，您需要启用检查堆调试令牌。 请参阅调试令牌的描述部分。 默认情况下，这将导致每次调用 dmalloc 时都对堆进行全面检查，无论它是 malloc、free、realloc 还是其他 dmalloc 重载函数。

执行完整堆检查可能会占用大量 CPU，并且您可能希望偶尔运行它。 这可以通过几种不同的方式来完成，包括 dmalloc 实用程序的“-i”间隔参数。 请参阅 Dmalloc 实用程序部分。 这将导致检查每 N 次运行一次。 例如，“dmalloc -i 3”将导致在每次第三次调用内存函数之前检查堆。 对于高内存使用率的程序，值 100 甚至 1000 比较小的程序更有用。

您还可以使程序在某个点之后开始执行详细的堆检查。 例如，使用“dmalloc -s 1000”选项，您可以告诉 dmalloc 库在第 1000 次内存调用后启用堆检查。 如果您在“settings.h”文件中启用了 LOG_ITERATION_COUNT，请检查生成的 dmalloc 日志文件并使用迭代计数。

开始选项也可以采用“file:line”格式。 例如，如果设置为“dmalloc_t.c:126”，dmalloc 将在看到来自“dmalloc_t.c”文件（第 126 行）的 dmalloc 调用后开始检查堆。如果使用“dmalloc_t.c:0” '，行号为 0，然后 dmalloc 在看到来自 'dmalloc_t.c' 文件中任何位置的调用后将开始检查堆。

## 3. How to program with the library.

### 3.1 Macros providing file and line information.

### 3.2 Getting caller address information.

### 3.3 Checking of function arguments.

### 3.4 Generating a core file on errors for debugging.

### 3.5 Additional non-standard routines

### 3.6 Description of the internal error numbers.

### 3.7 How to disable the library.

### 3.8 Using the library with C++.

### 3.9 Using a debugger with the library.

### 3.10 Using the library with a thread package.

### 3.11 Using the library with Cygwin environment.

### 3.12 Debugging memory in a server or cgi-bin process.

### 3.13 Explanation of the Logfile Output.

### 3.14 Various other hints that may help.

## How to use the library’s utility.

