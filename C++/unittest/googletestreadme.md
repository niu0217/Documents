# googletestreadme

## 通用构建说明

### Setup

要构建 GoogleTest 以及使用它的测试，您需要告诉构建系统在哪里可以找到其标头和源文件。 确切的方法取决于您使用的构建系统，并且通常很简单。

## Build with CMake

GoogleTest 附带一个 CMake 构建脚本 (`CMakeLists.txt`)，可在多种平台上使用（“C”代表跨平台）。 如果您尚未安装 CMake，可以从 https://cmake.org/ 免费下载。

CMake 的工作原理是生成可在您选择的编译器环境中使用的本机 makefile 或构建项目。 您可以将 GoogleTest 构建为独立项目，也可以将其合并到另一个项目的现有 CMake 构建中。

### 独立 CMake 项目

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

### 合并到现有的 CMake 项目中

如果您想在已经使用 CMake 的项目中使用 GoogleTest，最简单的方法是获取已安装的库和标头。

+ 使用 `find_package`（或 `pkg_check_modules`）导入 GoogleTest。 例如，如果 `find_package(GTest CONFIG REQUIRED) `成功，则可以使用 `GTest::gtest`、`GTest::gmock` 等库。

更强大和灵活的方法是直接将 GoogleTest 构建为该项目的一部分。 这是通过使 GoogleTest 源代码可用于主构建并使用 CMake 的 `add_subdirectory()` 命令添加来完成的。 这样做的一个显着优点是，GoogleTest 和项目的其余部分之间使用相同的编译器和链接器设置，因此可以避免与使用不兼容的库（例如调试/发布）等相关的问题。 这在 Windows 上特别有用。 可以通过几种不同的方式来使 GoogleTest 的源代码可用于主构建：

+ 手动下载 GoogleTest 源代码并将其放置在已知位置。 这是最不灵活的方法，并且可能会使其更难以与持续集成系统等一起使用。
+ 将 GoogleTest 源代码作为直接副本嵌入到主项目的源代码树中。 这通常是最简单的方法，但也是最难保持最新的。 有些组织可能不允许这种方法。
+ 添加 GoogleTest 作为 git 子模块或等效模块。 这可能并不总是可能或合适的。 例如，Git 子模块有其自身的优点和缺点。
+ 使用 CMake 下载 GoogleTest 作为构建配置步骤的一部分。 这种方法没有其他方法的局限性。

上述方法中的最后一个是通过一小段 CMake 代码实现的，该代码下载 GoogleTest 代码并将其拉入主构建中。

只需添加到您的 `CMakeLists.txt`：

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example example.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)
```

请注意，此方法需要 `CMake 3.14` 或更高版本，因为它使用 `FetchContent_MakeAvailable()` 命令。

**Visual Studio 动态与静态运行时**

默认情况下，新的 Visual Studio 项目动态链接 C 运行时，但 GoogleTest 静态链接它们。 这将生成如下所示的错误： `gtest.lib(gtest-all.obj) : error LNK2038: `检测到`“RuntimeLibrary”`不匹配：值“MTd_StaticDebug”与 main.obj 中的值“MDd_DynamicDebug”不匹配

GoogleTest 已经为此提供了一个 CMake 选项：`gtest_force_shared_crt`

启用此选项将使 gtest 也动态链接运行时，并匹配包含它的项目。

### C++ Standard Version

为了成功构建GoogleTest，需要支持C++14的环境。 确保这一点的一种方法是在顶级项目中指定标准，例如使用 `set(CMAKE_CXX_STANDARD 14)` 命令和 `set(CMAKE_CXX_STANDARD_REQUIRED ON)`。 如果这不可行，例如在使用 GoogleTest 进行验证的 C 项目中，则可以通过 `-DCMAKE_CXX_FLAGS` 选项将其添加到 cmake 的选项中来指定。

调整 GoogleTest

## 调整 GoogleTest

GoogleTest 可以在多种环境中使用。 在某些环境中，默认配置可能无法开箱即用（或可能无法正常工作）。 但是，您可以通过在编译器命令行上定义控制宏来轻松调整 GoogleTest。 通常，这些宏的命名类似于 `GTEST_XYZ`，您可以将它们定义为 1 或 0 以启用或禁用特定功能。

我们在下面列出了最常用的宏。 有关完整列表，请参阅文件 `include/gtest/internal/gtest-port.h`。

## 多线程测试

GoogleTest 在 `pthread` 库可用的情况下是线程安全的。 在 `#include <gtest/gtest.h>` 之后，您可以检查 `GTEST_IS_THREADSAFE` 宏以查看是否是这种情况（如果该宏 #define 为 1，则为 yes，如果未定义则为 no）。

如果 GoogleTest 无法正确检测 pthread 在您的环境中是否可用，您可以使用以下命令强制它

```bash
-DGTEST_HAS_PTHREAD=1
```

or

```bash
-DGTEST_HAS_PTHREAD=0
```

当 GoogleTest 使用 pthread 时，您可能需要向编译器和/或链接器添加标志以选择 pthread 库，否则您将收到链接错误。 如果您使用 CMake 脚本，系统会为您处理好这一问题。 如果您使用自己的构建脚本，则需要阅读编译器和链接器手册以找出要添加的标志。

## 作为共享库 (DLL)

GoogleTest 很紧凑，因此为了简单起见，大多数用户可以将其构建并链接为静态库。 如果您愿意，可以选择将 GoogleTest 用作共享库（在 Windows 上称为 DLL）。

要将 gtest 编译为共享库，请添加:

```bash
-DGTEST_CREATE_SHARED_LIBRARY=1
```

到编译器标志。 您还需要告诉链接器生成一个共享库 - 请参阅链接器手册以了解如何执行此操作。

要编译使用 gtest 共享库的测试，请添加

```bash
-DGTEST_LINKED_AS_SHARED_LIBRARY=1
```

to the compiler flags.

注意：虽然今天使用某些编译器（例如 GCC）时上述步骤在技术上不是必需的，但如果我们决定提高加载库的速度（请参阅 https://gcc.gnu），它们将来可能会变得必要。 org/wiki/Visibility 了解详细信息）。 因此，建议您在使用 GoogleTest 作为共享库时始终添加上述标志。 否则，GoogleTest 的未来版本可能会破坏您的构建脚本。

## 避免宏名称冲突

在 C++ 中，宏不遵守命名空间。 因此，如果您 #include 这两个定义，则两个都定义同名宏的库将会发生冲突。 如果 GoogleTest 宏与另一个库发生冲突，您可以强制 GoogleTest 重命名其宏以避免冲突。

具体来说，如果 GoogleTest 和其他一些代码都定义了宏 FOO，您可以添加

```bash
-DGTEST_DONT_DEFINE_FOO=1
```

到编译器标志，告诉 GoogleTest 将宏的名称从 FOO 更改为 GTEST_FOO。 目前 FOO 可以是 ASSERT_EQ、ASSERT_FALSE、ASSERT_GE、ASSERT_GT、ASSERT_LE、ASSERT_LT、ASSERT_NE、ASSERT_TRUE、EXPECT_FALSE、EXPECT_TRUE、FAIL、SUCCEED、TEST 或 TEST_F。 例如，使用 -DGTEST_DONT_DEFINE_TEST=1，您需要编写

```bash
GTEST_TEST(SomeTest, DoesThis) { ... }
```

instead of

```bash
TEST(SomeTest, DoesThis) { ... }
```

in order to define a test.