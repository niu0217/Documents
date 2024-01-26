# dmalloc

参考网址：

https://www.cnblogs.com/wangkangluo1/archive/2012/06/05/2535509.html

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

通过在 C 文件中包含“dmalloc.h”，对 malloc、calloc、realloc、recalloc、memalign、valloc、strdup 和 free 的调用将替换为对带有各种标志的 _dmalloc_malloc、_dmalloc_realloc 和 _dmalloc_free 的调用。 此外，该库还将对 xmalloc、xcalloc、xrealloc、xrecalloc、xmemalign、xvalloc、xstrdup 和 xfree 的调用替换为关联调用。

这些宏使用 c 预处理器 `__FILE__` 和 `__LINE__ `宏，它们在编译时被替换为相关源代码的当前文件和行号。 例程使用此信息来生成有关内存问题的详细报告。

```bash
not freed: '0x38410' (22 bytes) from 'dmalloc_t.c:92'
```

日志文件中的这一行显示内存未从文件“dmalloc_t.c”第 92 行中释放。请参阅“跟踪未释放内存”部分。

您可能会注意到上面列表中的一些非标准内存分配函数。 Recalloc 是一个类似于 realloc 的例程，它将先前分配的内存重新分配到新的大小。 如果新内存大小大于旧内存大小，recalloc 会将新空间初始化为全零。 您的操作系统本身可能支持也可能不支持。 Memalign 与 malloc 类似，但应确保返回的指针与一定数量的指定字节对齐。 目前，该库不支持 memalign 函数。 对于小于块大小的对齐值，它默认返回可能未对齐的内存。 Valloc 与 malloc 类似，但确保返回的指针与页边界对齐。 您的操作系统可能支持也可能不支持，但库完全支持。 Strdup 是一个字符串复制例程，它接受一个以 null 结尾的字符串指针，并返回一个已分配的字符串副本，稍后需要将该副本传递给 free 来释放。

标准内存函数（xmalloc、xfree 等）的 X 版本将向标准错误打印一条错误消息，并且如果库无法分配任何额外内存，则会停止。 使用这些例程而不是在程序中到处检查返回 NULL 指针的分配例程是很有用的。

警告：如果您在源代码中包含“dmalloc.h”文件，建议将其放在包含文件列表的末尾，因为 dmalloc 使用宏，并且可能会尝试更改其后的 malloc 函数的声明 。

### 3.2 Getting caller address information.

尽管分配宏可以为您的某些代码提供文件/行信息，但仍然有一些模块您不能包含“dmalloc.h”（例如库例程）或者您只是不想包含。 您仍然可以从返回地址信息中获取有关调用 dmalloc 函数的例程的信息。 要实现此目的，您必须在受支持的体系结构/编译器之一上使用此库。 请参阅移植库的重要问题部分。

该库尝试使用一些汇编技巧来获取返回地址或调用 dmalloc 函数的行的地址。 如果您的未释放内存没有关联的文件和行信息，您可能会看到以下未释放内存消息。

```bash
not freed: '0x38410' (22 bytes) from 'ra=0xdd2c'
not freed: '0x38600' (10232 bytes) from 'ra=0x10234d'
not freed: '0x38220' (137 bytes) from 'ra=0x82cc'
```

在调试器的帮助下，可以识别这些返回地址（或 ra）。 我在“contrib/”目录中提供了一个“ra_info.pl”perl 脚本，其中包含 dmalloc 源代码，该脚本似乎与 gdb 配合得很好。 您还可以使用 gdb 的手动方法来查找返回地址位置。 请参阅将返回地址转换为代码位置部分。

### 3.3 Checking of function arguments.

该库及其大量检查和诊断的一个潜在问题是，它们仅在调用 dmalloc 函数时才会执行。 一种解决方案是包含“dmalloc.h”并使用定义的 DMALLOC_FUNC_CHECK 标志编译源代码并启用 check-funcs 令牌。 请参阅调试令牌的描述部分。

```bash
cc -DDMALLOC -DDMALLOC_FUNC_CHECK file.c
```

注意：在启用 DMALLOC_FUNC_CHECK 的情况下编译源代码后，您必须在关闭它的情况下重新编译以断开库连接。 请参阅如何禁用该库部分。

警告：您应该确保在包含文件列表的末尾包含“dmalloc.h”，因为 dmalloc 使用宏，并且可能会尝试更改已检查函数的声明（如果它们位于其后面）。

定义此值后，dmalloc 将覆盖许多函数，并插入一个知道如何检查其自身参数然后调用实际函数的例程。 Dmalloc 可以检查 bcopy、index、strcat 和 strcasecmp 等函数。 有关完整列表，请参阅“dmalloc.h”的末尾。

例如，当您调用 strlen 时，dmalloc 将确保字符串参数的栅栏柱区域未被覆盖、其文件和行号位置良好等。使用 bcopy，dmalloc 将确保目标字符串有足够的空间 存储指定的字节数。

对于所有检查的参数，如果指针不在堆中，则它会被忽略，因为 dmalloc 对此一无所知。

### 3.4 Generating a core file on errors for debugging.

如果启用了错误中止调试令牌，当库检测到堆内存有任何问题时，它将立即尝试转储核心文件。 请参阅调试令牌的描述部分。 核心文件是程序及其状态的完整副本，调试器可以使用它来查看错误发生时具体发生了什么。 请参阅将 Dmalloc 与调试器一起使用部分。 默认情况下，库实用程序的 low、medium 和 high 参数启用错误中止标记。 您可以通过输入 dmalloc -m error-abort（-m 表示减号）来禁用此功能，以删除错误中止标记，您的程序将仅记录错误并继续。 您还可以使用错误转储令牌，该令牌在看到错误但仍继续运行时尝试转储核心。 请参阅调试令牌的描述部分。

当程序转储核心时，系统会将程序及其所有内存写入磁盘上通常名为“core”的文件。 如果您的程序名为“foo”，那么您的系统可能会将核心转储为“foo.core”。 如果您没有获得“核心”文件，请确保您的程序没有更改为新目录，这意味着它可能已将核心文件写入到不同的位置。 还要确保您的程序对其所在目录具有写入权限，否则它将无法转储核心文件。 核心转储通常是安全问题，因为它们包含所有程序内存，因此系统经常阻止它们的生成。 您需要检查用户和系统的核心转储大小 ulimit 设置。

默认情况下，该库使用 abort 函数来转储核心，该函数可能会也可能不会工作，具体取决于您的操作系统。 如果以下程序不转储核心，那么这可能就是问题所在。 请参阅“settings.dist”中的 KILL_PROCESS 定义。

```c
main()
{
   abort();
}
```

如果 abort 确实有效，那么您可能需要尝试“settings.dist”中的以下设置。 此代码尝试通过取消引用 NULL 指针来生成分段错误。

```c
#define KILL_PROCESS    { int *_int_p = 0L; *_int_p = 1; }
```

### 3.5 Additional non-standard routines

### 3.6 Description of the internal error numbers.

以下错误代码在‘error_val.h’中定义。 库使用它们来指示检测到的问题。 它们可能是由用户引起的（“ERROR_TOO_BIG”），也可能表明内部库问题（“ERROR_SLOT_CORRUPT”）。 ‘dmalloc’实用程序可以使用 -e 参数为您提供错误的字符串版本：

```bash
$ dmalloc -e 60
dmalloc: dmalloc_errno value '60' = 
   'pointer is not on block boundary'
```

以下是库设置的错误代码。 它们故意不连续，因为我一直添加和删除代码，并且有针对各种错误代码类型的部分。

1. `1 (ERROR_NONE) no error`

   没有错误。 将无错误代码设置为非 0 值是一种很好的编码习惯，因为它会强制您显式设置它。

2. `2 (INVALID_ERROR)`

   错误编号无效。 如果库输出此错误，则您的 dmalloc 实用程序可能与您链接的库相比已经过时。 这将与此处未列出的所有错误代码一起返回。

3. `10 (ERROR_BAD_SETUP) initialization and setup failed`

   设置值错误。 目前尚未使用，但其目的是报告无效的设置配置信息。

4. `11 (ERROR_IN_TWICE) malloc library has gone recursive`

   library递归了。 这通常表明您没有使用该库的线程版本。 或者，如果您是，那么您没有使用“-o”“锁定”选项。 请参阅将库与线程包一起使用部分。

5. `13 (ERROR_LOCK_NOT_CONFIG) thread locking has not been configured`

   尚未配置线程锁定。 这表明您尝试使用“-o”“锁定”选项而不链接到库的线程版本。 链接时您可能应该使用 -ldmallocth 而不是 -ldmalloc。 或者您应该在编译行中包含…/lib/libdmallocth.a。

6. `20 (ERROR_IS_NULL) pointer is null`

   指针为空。 程序将 NULL (0L) 指针传递给 free，并且您启用了 error-free-null 标记。

7. `21 (ERROR_NOT_IN_HEAP) pointer is not pointing to heap data space`

   指针未指向堆数据空间。 这意味着程序将越界指针传递给 free 或 realloc。 这可能是有人尝试使用野指针或尝试从与 malloc 不同的源释放指针。

8. `22 (ERROR_NOT_FOUND) cannot locate pointer in heap`

   无法在堆中找到指针。 用户传递了一个堆不知道的指针。 该指针要么是由其他机制分配的（例如直接 mmap 或 sbrk），要么是随机无效指针。

   在某些罕见的情况下，有时会在共享库中看到，程序中可能有 dmalloc 库的两个单独的副本。 每个人都不知道对方分配的指针。

9. `23 (ERROR_IS_FOUND) found pointer the user was looking for`

   这表明库发现了环境变量地址部分中指定的指针。 请参阅环境变量名称和功能部分。 此错误很有用，因此您可以在调试器中放置断点来查找分配特定地址的位置。 请参阅将 Dmalloc 与调试器一起使用部分。

10. `24 (ERROR_BAD_FILE) possibly bad .c filename pointer`

    在 dmalloc 管理部分中发现了可能无效的文件名。 这可能表明内部表存在一些损坏。 这也可能意味着您的源文件名称超过 100 个字符。 请参阅“settings.dist”文件中的 MAX_FILE_LENGTH。

11. `25 (ERROR_BAD_LINE) possibly bad .c file line-number`

    dmalloc 管理部分中的行号超出范围。 这可能表明内部表存在一些损坏。 它还可能意味着您的源文件包含超过 30000 行代码。 请参阅“settings.dist”文件中的 MAX_LINE_NUMBER。

12. `26 (ERROR_UNDER_FENCE) failed UNDER picket-fence magic-number check`

    这表明指针的下界栅栏幻数已被覆盖。 如果启用了 check-fence 令牌，则库会在分配的上方和下方写入魔法值以防止溢出。 这很可能是因为它下面的指针超出了它的分配范围并写入了下一个指针的空间。

13. `27 (ERROR_OVER_FENCE) failed OVER picket-fence magic-number check`

    这表明指针的上限尖桩栅栏魔法空间已被覆盖。 如果启用了 check-fence 令牌，则库会在分配的上方和下方写入魔法值以防止溢出。 这很可能是因为数组或字符串分配写入超过了分配末尾。

    检查 strcat、sprintf、strcpy 以及任何其他处理字符串且不通过跟踪字符串大小来保护自身的函数是否使用不当。 这些函数应始终替换为：strncat、snprintf、strncpy 等。

14. `28 (ERROR_WOULD_OVERWRITE) use of pointer would exceed allocation`

    此错误是由通常使用 check-funcs 标记启用的函数指针检查代码生成的。 Dmalloc 重载了许多字符串和内存复制函数，并验证缓冲区（如果在堆中分配）不会被函数覆盖。

15. `30 (ERROR_NOT_START_BLOCK) pointer is not to start of memory block`

    这表明用户传入了一个要释放或重新分配的指针，该指针不在分配开始时。 例如，如果您分配并获取指针 X 但随后尝试释放 X+1，则会出现此错误。

16. `40 (ERROR_BAD_SIZE) invalid allocation size`

    此错误表明库内部结构中的大小值已损坏。 这可能是随机指针问题、指针溢出或其他一些损坏。

17. `41 (ERROR_TOO_BIG) largest maximum allocation size exceeded`

    分配请求的内存大于配置的最大值。 这是用户配置的设置。 请参阅“settings.dist”文件中的“LARGEST_ALLOCATION”。 它用于防止疯狂的分配大小。 如果您有超大的分配大小，那么您应该适当调整 LARGEST_ALLOCATION 值。

18. `43 (ERROR_ALLOC_FAILED) could not grow heap by allocating memory`

    库无法分配更多堆空间，程序内存不足。 这可能表明您已经超出了某些系统施加的限制。 在许多操作系统上，ulimit 调用可以调整系统默认值。 与系统 malloc 库相比，该库使用更多内存，因为它存储了更多有关已分配指针的信息。

    注意：这也可能是由于您的操作系统无法使用 mmap 系统调用来分配内存。 您可能需要将 USE_MMAP 设置强制为 0。请使用 URL http://dmalloc.com/ 的论坛报告与此相关的问题。

19. `45 (ERROR_OVER_LIMIT) over user specified allocation limit`

    该库分配的内存多于内存限制环境变量中指定的内存。 请参阅环境变量名称和功能部分。

20. `60 (ERROR_NOT_ON_BLOCK) pointer is not on block boundary`

    用户尝试释放或重新分配未指向块边界的指针。 例如，如果您分配并获取指针 X 但随后尝试释放 X+1，则会出现此错误。

21. `61 (ERROR_ALREADY_FREE) tried to free previously freed pointer`

    用户尝试释放已释放的指针。 这是一个非常常见的错误，可能会导致严重的问题。 这可能是因为析构函数由于某种原因被调用两次。 尽管强烈建议跟踪特定源，但通常在释放指针后将指针设置为 NULL (0L) 是很好的做法。

22. `67 (ERROR_FREE_OVERWRITTEN) free space has been overwritten`

    如果启用了 free-blank 或 check-blank 标记，则当使用“dmalloc-free”字节（十六进制 0xdf，八进制 0337，十进制 223）释放内存时，库将覆盖内存。 如果程序写入此空间，则库将检测到写入并触发此错误。 这可能表明程序正在使用释放后的指针。

23. `70 (ERROR_ADMIN_LIST) bad admin structure list`

    Lirary管理结构中发现了内部腐败。 这可能是随机指针问题、指针溢出或其他一些损坏。

24. `72 (ERROR_ADDRESS_LIST) internal address list corruption`

    Lirary管理结构中发现了内部腐败。 这可能是随机指针问题、指针溢出或其他一些损坏。

25. `73 (ERROR_SLOT_CORRUPT) internal memory slot corruption`

    Lirary管理结构中发现了内部腐败。 这可能是随机指针问题、指针溢出或其他一些损坏。

### 3.7 How to disable the library.

如果您想在特别分配密集的代码部分禁用库的详细检查功能，您可以执行以下操作：

```c
unsigned int dmalloc_flags;
…
/* turn off all debug flags and save a copy of old value */
dmalloc_flags = dmalloc_debug(0);

/* section of a lot of allocations */
…
/* end of section */

/* restore the dmalloc flag setting */
dmalloc_debug(dmalloc_flags);
```

当您完成开发和调试会话后，您可能需要禁用 dmalloc 库，并将系统的内存分配例程、gnu-malloc 或您自己的内存分配例程放在其位置上。 我们已尝试使这一过程变得相当轻松。 提取的难易程度在很大程度上取决于您在编码过程中使用了多少库的功能。

欢迎就如何改进此过程同时保持调试有效性提出合理建议。

+ 如果您想完全禁用 dmalloc 库，那么您需要在定义 DMALLOC_DISABLE 时重新编译包含“dmalloc.h”的所有 C 文件。 这将导致 dmalloc 宏不被应用。 请参阅提供文件和行信息的宏部分。

```bash
cc -g -DDMALLOC_DISABLE file.c
```

另一种方法是用 #ifdef DMALLOC 包围 dmalloc.h 包含或任何直接 dmalloc 引用，然后删除 -DDMALLOC。

```c
#ifdef DMALLOC
#include "dmalloc.h"
#endif

main()
{
   …

#ifdef DMALLOC
   dmalloc_verify(0L);
#endif
   return 0;
}
 	
// to get dmalloc information
$ cc -DDMALLOC main.c

// without dmalloc information
$ cc main.c
```

+ 如果您编译了定义了 DMALLOC_FUNC_CHECK 的任何源模块，则必须首先在未启用该标志的情况下重新编译所有这些模块。
  如果您已使用 DMALLOC_DISABLED 标志禁用 dmalloc，或者从未在任何 C 文件中包含“dmalloc.h”，那么当您需要禁用该库时，无需重新编译源代码。

  如果您收到未解析的引用，例如 _dmalloc_malloc 或 _dmalloc_bcopy，则某些内容未按应有的方式禁用。

### 3.8 Using the library with C++.

对于那些使用 C++ 语言的人，该库尝试配置和构建“libdmallocxx.a”库。 该库应该链接到您的 C++ 程序而不是“libdmalloc.a”。

Dmalloc 在 C++ 中的表现不如 C，因为 C++ 中的动态内存例程是 new() 和 delete()，而不是 malloc() 和 free()。 由于 new 和 delete 通常不用作函数，而是用作 x = new 类型，因此遗憾的是 dmalloc 没有简单的方法来传递文件和行信息。 “libdmallocxx.a”库提供了“dmallocc.cc”文件，该文件有效地将 new 重定向到更熟悉的 malloc，并将删除重定向到更熟悉的 free。

注意：作者不是 C++ 黑客，因此我们非常感谢 C++ 用户以其他提示和想法的形式提供反馈。

### 3.9 Using a debugger with the library.

以下是使用 dmalloc 库来跟踪程序问题的多种可能场景。

您应该首先启用日志文件文件名并打开一组调试功能。 您可以使用 `dmalloc -l logfile low` 来完成此操作。 如果您也有兴趣将错误消息打印到终端，请随后键入 `dmalloc -p print-messages` 来启用 print-messages 令牌。 请参阅 Dmalloc 实用程序部分。

现在您可以输入调试器（我使用优秀的 GNU 调试器 gdb），并在 dmalloc_error() 中放置一个断点，这是库的内部错误例程。 当您的程序运行时，如果检测到内存问题，它将停止在那里。

如果您使用 GDB，我建议将“contrib”子目录中“dmalloc.gdb”的内容添加到主目录中的“.gdbinit”文件中。 这将启用 dmalloc 命令，该命令将提示您输入 dmalloc 命令的参数，并自动在 dmalloc_error() 中设置断点。

如果您使用共享库，您可能需要首先执行以下命令来加载 dmalloc 和其他库符号：

```bash
(gdb) sharedlibrary
(gdb) add-shared-symbol-files
```

### 3.10 Using the library with a thread package.

### 3.11 Using the library with Cygwin environment.

### 3.12 Debugging memory in a server or cgi-bin process.

### 3.13 Explanation of the Logfile Output.

### 3.14 Various other hints that may help.

## 4. How to use the library’s utility.

