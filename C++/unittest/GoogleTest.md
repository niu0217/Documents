# GoogleTest

## 公告

### Live at Head

GoogleTest 现在遵循 `Abseil Live at Head` 理念。 我们建议尽可能频繁地更新到主分支中的最新提交。 我们偶尔会发布语义版本，标记为 `v${major}.${minor}.${patch}`（例如 `v1.14.0`）。

### Documentation Updates

我们的文档现已发布在 GitHub Pages 上：https://google.github.io/googletest/。 我们建议浏览 GitHub Pages 上的文档，而不是直接在存储库中浏览。

### Release 1.14.0

[Release 1.14.0](https://github.com/google/googletest/releases/tag/v1.14.0) is now available.

The 1.14.x branch requires at least C++14.

### 持续集成

我们使用 Google 的内部系统进行持续集成。
添加 GitHub Actions 是为了方便开源贡献者。 它们由开源社区独家维护，GoogleTest 团队不使用。

### 即将推出

- We are planning to take a dependency on [Abseil](https://github.com/abseil/abseil-cpp).
- More documentation improvements are planned.

## Welcome to **GoogleTest**, Google's C++ test framework!

该存储库是以前独立的 GoogleTest 和 GoogleMock 项目的合并。 它们之间的关系非常密切，因此将它们一起维护和发布是有意义的。

### Getting Started

See the [GoogleTest User's Guide](https://google.github.io/googletest/) for documentation. We recommend starting with the [GoogleTest Primer](https://google.github.io/googletest/primer.html).

More information about building GoogleTest can be found at [googletest/README.md](https://github.com/google/googletest/blob/main/googletest/README.md).

### 特征

+ xUnit测试框架：
  Googletest 基于 xUnit 测试框架，这是一种流行的单元测试架构
+ 测试发现：
  Googletest 自动发现并运行您的测试，无需手动注册您的测试
+ 丰富的断言集：
  Googletest提供了多种断言，例如相等、不等、异常等，使您可以轻松测试代码
+ 用户定义的断言：
  您可以使用 Googletest 定义自己的断言，从而可以轻松编写特定于您的代码的测试
+ 死亡测试：
  Googletest 支持死亡测试，它验证您的代码是否以某种方式退出，这对于测试错误处理代码非常有用
+ 致命和非致命故障：
  您可以使用 Googletest 指定测试失败是否应被视为致命或非致命，从而允许测试在发生失败时继续运行
+ 值参数化测试：
  Googletest 支持值参数化测试，可以使用不同的输入值运行多次，这对于测试采用不同输入的函数非常有用
+ 类型参数化测试：
  Googletest 还支持类型参数化测试，该测试使用不同的数据类型运行，这对于测试使用不同数据类型的函数非常有用
+ 运行测试的各种选项：
  Googletest 提供了许多运行测试的选项，包括运行单独的测试、按特定顺序运行测试以及并行运行测试

### 支持的平台

GoogleTest follows Google's [Foundational C++ Support Policy](https://opensource.google/documentation/policies/cplusplus-support). See [this table](https://github.com/google/oss-policies-info/blob/main/foundational-cxx-support-matrix.md) for a list of currently supported versions of compilers, platforms, and build tools.

## Who Is Using GoogleTest?

除了 Google 的许多内部项目之外，GoogleTest 还被以下著名项目使用：

- The [Chromium projects](https://www.chromium.org/) (behind the Chrome browser and Chrome OS).
- The [LLVM](https://llvm.org/) compiler.
- [Protocol Buffers](https://github.com/google/protobuf), Google's data interchange format.
- The [OpenCV](https://opencv.org/) computer vision library.

## 相关开源项目

[GTest Runner](https://github.com/nholthaus/gtest-runner) is a Qt5 based automated test-runner and Graphical User Interface with powerful features for Windows and Linux platforms.

[GoogleTest UI](https://github.com/ospector/gtest-gbar) is a test runner that runs your test binary, allows you to track its progress via a progress bar, and displays a list of test failures. Clicking on one shows failure text. GoogleTest UI is written in C#.

[GTest TAP Listener](https://github.com/kinow/gtest-tap-listener) is an event listener for GoogleTest that implements the [TAP protocol](https://en.wikipedia.org/wiki/Test_Anything_Protocol) for test result output. If your test runner understands TAP, you may find it useful.

[gtest-parallel](https://github.com/google/gtest-parallel) is a test runner that runs tests from your binary in parallel to provide significant speed-up.

[GoogleTest Adapter](https://marketplace.visualstudio.com/items?itemName=DavidSchuldenfrei.gtest-adapter) is a VS Code extension allowing to view GoogleTest in a tree view and run/debug your tests.

[C++ TestMate](https://github.com/matepek/vscode-catch2-test-adapter) is a VS Code extension allowing to view GoogleTest in a tree view and run/debug your tests.

[Cornichon](https://pypi.org/project/cornichon/) is a small Gherkin DSL parser that generates stub code for GoogleTest.

## 贡献改变

Please read [`CONTRIBUTING.md`](https://github.com/google/googletest/blob/main/CONTRIBUTING.md) for details on how to contribute to this project.

Happy testing!

