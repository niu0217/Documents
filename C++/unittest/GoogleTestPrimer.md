# GoogleTestPrimer

## 简介：为什么选择 GoogleTest？

GoogleTest 可帮助您编写更好的 C++ 测试。

GoogleTest 是测试技术团队根据 Google 的特定要求和限制开发的测试框架。 无论您在 Linux、Windows 还是 Mac 上工作，如果您编写 C++ 代码，GoogleTest 都可以为您提供帮助。 它支持任何类型的测试，而不仅仅是单元测试。

那么什么才是好的测试，GoogleTest 如何融入其中呢？ 我们相信：

1. 测试应该是独立且可重复的。 调试因其他测试而成功或失败的测试是一件痛苦的事情。 GoogleTest 通过在不同的对象上运行每个测试来隔离测试。 当测试失败时，GoogleTest 允许您单独运行它以进行快速调试。
2. 测试应该组织良好并反映被测试代码的结构。 GoogleTest 将相关测试分组到可以共享数据和子例程的测试套件中。 这种常见模式很容易识别，并且使测试易于维护。 当人们切换项目并开始使用新的代码库时，这种一致性特别有用。
3. 测试应该是便携式和可重复使用的。 Google 有很多平台中立的代码； 它的测试也应该是平台中立的。 GoogleTest 适用于不同的操作系统、不同的编译器，无论是否有例外，因此 GoogleTest 测试可以使用各种配置。
4. 当测试失败时，他们应该提供尽可能多的有关问题的信息。 GoogleTest 不会在第一次测试失败时停止。 相反，它仅停止当前测试并继续下一个测试。 您还可以设置报告非致命故障的测试，然后继续当前测试。 因此，您可以在单个运行-编辑-编译周期中检测并修复多个错误。
5. 测试框架应该将测试编写者从家务劳动中解放出来，让他们专注于测试内容。 GoogleTest 自动跟踪所有定义的测试，并且不需要用户枚举它们来运行它们。
6. 测试应该很快。 借助 GoogleTest，您可以在测试之间重复使用共享资源，并且只需支付一次设置/拆卸费用，而不会使测试相互依赖。

由于 GoogleTest 基于流行的 xUnit 架构，因此如果您以前使用过 JUnit 或 PyUnit，您将会感到宾至如归。 如果没有，您将需要大约 10 分钟来学习基础知识并开始使用。 那么我们走吧！

## 注意命名法

> 注意：术语“测试”、“测试用例”和“测试套件”的不同定义可能会引起一些混淆，因此请小心误解它们。
>
> *Note:* There might be some confusion arising from different definitions of the terms *Test*, *Test Case* and *Test Suite*, so beware of misunderstanding these.

从历史上看，GoogleTest 开始使用术语“测试用例”来对相关测试进行分组，而当前的出版物，包括国际软件测试资格委员会 (ISTQB) 材料和各种有关软件质量的教科书，则使用术语“测试套件”。

GoogleTest 中使用的相关术语“测试”对应于 ISTQB 和其他术语的“测试用例”。

“测试”一词通常具有足够广泛的含义，包括 ISTQB 对测试用例的定义，因此这里不是什么大问题。 但 Google Test 中使用的“测试用例”一词具有矛盾的含义，因此令人困惑。

GoogleTest 最近开始用测试套件替换术语“测试用例”。 首选 API 是 TestSuite。 旧的 TestCase API 正在慢慢被弃用和重构。

因此，请注意术语的不同定义：

| Meaning                                                      | GoogleTest Term                                              | [ISTQB](https://www.istqb.org/) Term                         |
| :----------------------------------------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| Exercise a particular program path with specific input values and verify the results | [TEST()](https://google.github.io/googletest/primer.html#simple-tests) | [Test Case](https://glossary.istqb.org/en_US/term/test-case-2) |

## 基本概念

使用 GoogleTest 时，您首先要编写断言，这些断言是检查条件是否为真的语句。 断言的结果可以是成功、非致命失败或致命失败。 如果发生致命故障，则中止当前功能； 否则程序将正常继续。

测试使用断言来验证测试代码的行为。 如果测试崩溃或者断言失败，那么它就失败了； 否则就会成功。

测试套件包含一个或多个测试。 您应该将测试分组到反映测试代码结构的测试套件中。 当测试套件中的多个测试需要共享公共对象和子例程时，可以将它们放入测试夹具类中。

一个测试程序可以包含多个测试套件。

我们现在将解释如何编写测试程序，从单独的断言级别开始并构建测试和测试套件。

## 断言

GoogleTest 断言是类似于函数调用的宏。 您可以通过对其行为进行断言来测试类或函数。 当断言失败时，GoogleTest 会打印断言的源文件和行号位置以及失败消息。 您还可以提供自定义失败消息，该消息将附加到 GoogleTest 的消息中。

这些断言成对出现，测试相同的事物，但对当前函数有不同的影响。` ASSERT_*` 版本失败时会生成致命故障，并中止当前函数。 `EXPECT_*` 版本会生成非致命故障，不会中止当前函数。 通常` EXPECT_* `是首选，因为它们允许在测试中报告多个失败。 但是，如果当相关断言失败时继续没有意义，则应使用 `ASSERT_*`。

由于失败的` ASSERT_* `会立即从当前函数返回，可能会跳过其后面的清理代码，因此可能会导致空间泄漏。 根据泄漏的性质，它可能值得修复，也可能不值得修复 - 因此，如果除了断言错误之外还出现堆检查器错误，请记住这一点。

要提供自定义失败消息，只需使用 << 运算符或一系列此类运算符将其流式传输到宏中。 请参阅以下示例，使用 `ASSERT_EQ` 和 `EXPECT_EQ `宏来验证值相等：

```c++
ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

for (int i = 0; i < x.size(); ++i) {
  EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
}
```

任何可以流式传输到` ostream` 的内容都可以流式传输到断言宏，特别是 C 字符串和字符串对象。 如果将宽字符串（Windows 上的 UNICODE 模式下的 `wchar_t*`、`TCHAR*` 或` std::wstring`）流式传输到断言，则在打印时它将被转换为` UTF-8`。

GoogleTest 提供了一组断言，用于以各种方式验证代码的行为。 您可以检查布尔条件、基于关系运算符比较值、验证字符串值、浮点值等等。 甚至还有一些断言可以让您通过提供自定义谓词来验证更复杂的状态。 有关 GoogleTest 提供的断言的完整列表，请参阅断言参考。

## 简单测试

创建测试：

1. 使用 `TEST() `宏定义和命名测试函数。 这些是不返回值的普通 C++ 函数。
2. 在此函数中，与要包含的任何有效 C++ 语句一起，使用各种 GoogleTest 断言来检查值。
3. 测试的结果由断言决定； 如果测试中的任何断言失败（致命或非致命），或者测试崩溃，则整个测试失败。 否则，就成功了。

```c++
TEST(TestSuiteName, TestName) {
  ... test body ...
}
```

`TEST() `参数从一般到具体。 第一个参数是测试套件的名称，第二个参数是测试套件中测试的名称。 两个名称都必须是有效的 C++ 标识符，并且不应包含任何下划线 (_)。 测试的全名由其包含的测试套件及其单独的名称组成。 来自不同测试套件的测试可以具有相同的单独名称。

例如，我们来看一个简单的整数函数：

```c++
int Factorial(int n);  // Returns the factorial of n
```

A test suite for this function might look like:

```c++
// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(Factorial(1), 1);
  EXPECT_EQ(Factorial(2), 2);
  EXPECT_EQ(Factorial(3), 6);
  EXPECT_EQ(Factorial(8), 40320);
}
```

GoogleTest按测试套件对测试结果进行分组，因此逻辑上相关的测试应该位于同一个测试套件中； 换句话说，它们的 TEST() 的第一个参数应该是相同的。 在上面的示例中，我们有两个测试，`HandlesZeroInput `和 `HandlesPositiveInput`，它们属于同一测试套件 `FactorialTest`。

命名测试套件和测试时，应遵循与命名函数和类相同的约定。

可用性：Linux、Windows、Mac。

## 测试夹具：使用相同的数据配置进行多个测试

如果您发现自己正在编写两个或多个对相似数据进行操作的测试，则可以使用测试装置。 这允许您为多个不同的测试重用相同的对象配置。

要创建夹具：

1. 从`test::Test` 派生一个类。 以 `protected:` 开始它的主体，因为我们想要从子类访问固定装置成员。
2. 在类中，声明您计划使用的任何对象。
3. 如有必要，请编写默认构造函数或 `SetUp()` 函数来为每个测试准备对象。 一个常见的错误是将 `SetUp() `拼写为带有小 u 的 Setup() - 在 C++11 中使用 `override` 来确保拼写正确。
4. 如有必要，请编写析构函数或 `TearDown()` 函数来释放您在 `SetUp()` 中分配的任何资源。 要了解何时应使用构造函数/析构函数以及何时应使用 `SetUp()/TearDown()`，请阅读常见问题解答。
5. 如果需要，定义子例程供您的测试共享。

使用夹具时，请使用 `TEST_F()` 而不是 `TEST()`，因为它允许您访问测试夹具中的对象和子例程：

```c++
TEST_F(TestFixtureClassName, TestName) {
  ... test body ...
}
```

与 `TEST()` 不同，在 `TEST_F()` 中，第一个参数必须是测试装置类的名称。 （`_F` 代表“夹具”）。 没有为此宏指定测试套件名称。

不幸的是，C++ 宏系统不允许我们创建可以处理这两种类型的测试的单个宏。 使用错误的宏会导致编译器错误。

另外，在 `TEST_F()` 中使用测试夹具类之前，您必须首先定义它，否则您将收到编译器错误“虚拟外部类声明”。

对于使用 `TEST_F() `定义的每个测试，GoogleTest 将在运行时创建一个新的测试装置，立即通过 `SetUp()` 对其进行初始化，运行测试，通过调用 `TearDown()` 进行清理，然后删除测试装置。 请注意，同一测试套件中的不同测试具有不同的测试夹具对象，并且 GoogleTest 始终会在创建下一个测试夹具之前删除一个测试夹具。 GoogleTest 不会为多个测试重复使用相同的测试装置。 一项测试对夹具所做的任何更改都不会影响其他测试。

作为示例，让我们为名为 `Queue` 的 FIFO 队列类编写测试，该类具有以下接口：

```c++
template <typename E>  // E is the element type.
class Queue {
 public:
  Queue();
  void Enqueue(const E& element);
  E* Dequeue();  // Returns NULL if the queue is empty.
  size_t size() const;
  ...
};
```

首先，定义一个`fixture`类。 按照惯例，您应该将其命名为 `FooTest`，其中 `Foo` 是正在测试的类。

```c++
class QueueTest : public testing::Test {
 protected:
  void SetUp() override {
     // q0_ remains empty
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {}

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};

```

在这种情况下，不需要 `TearDown()`，因为除了析构函数已经完成的工作之外，我们不需要在每次测试后进行清理。

现在我们将使用 `TEST_F()` 和这个固定装置编写测试。

```c++
TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
}

TEST_F(QueueTest, DequeueWorks) {
  int* n = q0_.Dequeue();
  EXPECT_EQ(n, nullptr);

  n = q1_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 1);
  EXPECT_EQ(q1_.size(), 0);
  delete n;

  n = q2_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 2);
  EXPECT_EQ(q2_.size(), 1);
  delete n;
}
```

上面同时使用了 `ASSERT_*` 和 `EXPECT_*` 断言。 经验法则是，当您希望测试在断言失败后继续揭示更多错误时，请使用 `EXPECT_*`，而当失败后继续没有意义时，请使用 `ASSERT_*`。 例如，Dequeue 测试中的第二个断言是 `ASSERT_NE(n, nullptr)`，因为我们需要稍后取消引用指针 n，这会在 n 为 NULL 时导致段错误。

当这些测试运行时，会发生以下情况：

1. GoogleTest 构造一个 `QueueTest` 对象（我们称之为 t1）。
2. `t1.SetUp()` 初始化 t1。
3. 第一个测试 (`IsEmptyInitially`) 在 t1 上运行。
4. `t1.TearDown()` 在测试完成后进行清理。
5. t1 被破坏。
6. 在另一个 QueueTest 对象上重复上述步骤，这次运行 DequeueWorks 测试。

可用性：Linux、Windows、Mac。

## 调用测试

`TEST()` 和 `TEST_F()` 隐式向 GoogleTest 注册其测试。 因此，与许多其他 C++ 测试框架不同，您不必重新列出所有定义的测试来运行它们。

定义测试后，您可以使用 `RUN_ALL_TESTS()` 运行它们，如果所有测试都成功，则返回 0，否则返回 1。 请注意，`RUN_ALL_TESTS() `运行链接单元中的所有测试——它们可以来自不同的测试套件，甚至不同的源文件。

调用时，`RUN_ALL_TESTS() `宏：

+ 保存所有 GoogleTest 标志的状态。

+ 为第一个测试创建一个测试夹具对象。

+ 通过 `SetUp()` 对其进行初始化。

+ 在夹具对象上运行测试。

+ 通过 `TearDown()` 清理固定装置。

+ 删除夹具。

+ 恢复所有 GoogleTest 标志的状态。

+ 对下一个测试重复上述步骤，直到所有测试都运行完毕。

如果发生致命故障，则将跳过后续步骤。

> 重要提示：您不能忽略 RUN_ALL_TESTS() 的返回值，否则您将收到编译器错误。 这种设计的基本原理是，自动化测试服务根据其退出代码而不是其 stdout/stderr 输出来确定测试是否通过； 因此你的 main() 函数必须返回 RUN_ALL_TESTS() 的值。
>
> 另外，您应该只调用 RUN_ALL_TESTS() 一次。 多次调用它与一些高级 GoogleTest 功能（例如线程安全死亡测试）冲突，因此不受支持

可用性：Linux、Windows、Mac。

## 编写 main() 函数

大多数用户不需要编写自己的 main 函数，而是与 `gtest_main` 链接（而不是 `gtest`），它定义了合适的入口点。 有关详细信息，请参阅本节末尾。 本节的其余部分仅适用于您需要在测试运行之前执行一些无法在装置和测试套件框架内表达的自定义操作的情况。

如果您编写自己的主函数，它应该返回 `RUN_ALL_TESTS()` 的值。

您可以从这个样板开始：

```c++
#include "this/package/foo.h"

#include <gtest/gtest.h>

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
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

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {
  const std::string input_filepath = "this/package/testdata/myinputfile.dat";
  const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
  Foo f;
  EXPECT_EQ(f.Bar(input_filepath, output_filepath), 0);
}

// Tests that Foo does Xyz.
TEST_F(FooTest, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

`test::InitGoogleTest()` 函数解析命令行中的 GoogleTest 标志，并删除所有已识别的标志。 这允许用户通过各种标志来控制测试程序的行为，我们将在高级指南中介绍这些标志。 您必须在调用 `RUN_ALL_TESTS()` 之前调用此函数，否则标志将无法正确初始化。

在 Windows 上，`InitGoogleTest()` 也适用于宽字符串，因此它也可以在以 `UNICODE 模式`编译的程序中使用。

但也许您认为编写所有这些主要函数的工作量太大了？ 我们完全同意你的观点，这就是为什么 Google Test 提供了 main() 的基本实现。 如果它符合您的需求，那么只需将您的测试与 `gtest_main `库链接起来就可以了。

> 注意：ParseGUnitFlags() 已被弃用，取而代之的是 InitGoogleTest()。

## 已知限制

+ Google Test 被设计为线程安全的。 该实现在 `pthreads` 库可用的系统上是线程安全的。 目前，在其他系统（例如 Windows）上同时使用来自两个线程的 Google Test 断言是不安全的。 在大多数测试中，这不是问题，因为断言通常是在主线程中完成的。 如果您想提供帮助，您可以自愿在 `gtest-port.h` 中为您的平台实现必要的同步原语。

