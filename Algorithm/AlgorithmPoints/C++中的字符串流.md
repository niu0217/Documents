# C++中的字符串流

## 1. 引入

C++ 中的字符串流（stringstream）是一种特殊的流，它允许你像使用标准流一样使用字符串。字符串流可以让你将字符串当作流来处理，你可以向其输入数据，然后从中读取数据。这在某些情况下非常有用，比如将不同类型的数据组合成一个字符串，或者从字符串中提取各种类型的数据。

下面是一些使用字符串流的示例：

### 1.1 将数据写入字符串流

```c++
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    stringstream ss;
    int num = 123;
    double pi = 3.14;
    string name = "Alice";
    
    ss << "The number is: " << num << ", Pi is: " << pi << ", Name is: " << name;

    string result = ss.str(); // 获取字符串流中的内容
    cout << result << endl;

    return 0;
}
```

在这个示例中，我们将整数、浮点数和字符串写入了一个字符串流中，并将其结果作为一个字符串输出。`stringstream` 对象可以使用像`<<`这样的运算符来向其中写入各种类型的数据。

### 1.2 从字符串流中读取数据

```c++
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string data = "10 20 30 40 50";
    stringstream ss(data);
    int num;
    while(ss >> num) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
```

在这个示例中，我们创建了一个字符串流，将一个包含一系列空格分隔数字的字符串写入其中。然后我们从这个字符串流中逐个读取数字并打印出来。

字符串流能够将字符串和各种类型的数据相互转换，这使得在处理字符串时更为灵活和方便。

## 2. 举例

### 2.1 istringstream (输入字符串流)

`istringstream` 类用于从字符串中读取数据，并提供了类似于`istream`的接口，使得可以像从输入流中读取数据一样从字符串中读取数据。

示例1：从字符串中读取数据

```c++
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string data = "10 20 30 40 50";
    istringstream iss(data);
    int num;
    while(iss >> num) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
```

上述示例中，`istringstream`对象`iss`被用来将包含一系列用空格分隔的数字的字符串`data`解析为各个数字，并将它们打印出来。

### 2.2 ostringstream (输出字符串流)

`ostringstream` 类用于创建一个字符串流，可以像使用输出流一样向其中写入数据，并将结果以字符串的形式获取。

示例2：向字符串流中写入数据

```c++
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    ostringstream oss;
    int num = 123;
    double pi = 3.14;
    string name = "Alice";
    
    oss << "The number is: " << num << ", Pi is: " << pi << ", Name is: " << name;

    string result = oss.str(); // 获取字符串流中的内容
    cout << result << endl;

    return 0;
}
```

在这个示例中，`ostringstream`对象`oss`被用来将整数、浮点数和字符串写入其中，并将结果作为一个字符串输出。

## 3. 高级用法

### 3.1 ignore

#### 3.1.1 ignore(nCount, delim)

当使用 `ignore(nCount, delim)` 时，它的作用是从流中跳过指定数量的字符，或者直到遇到特定的定界字符 `delim` 为止。

- **nCount**：表示要跳过的字符的数量。如果 `nCount` 为特定的数值，则会忽略流中的这些字符。如果 `nCount` 为 `std::string::npos`，则会一直跳过直到遇到定界字符或者达到流的末尾。
- **delim**：表示定界字符，当遇到这个字符时，`ignore` 操作停止。如果没有提供 `delim`，则会一直跳过指定数量的字符（由 `nCount` 指定）。

```c++
#include <iostream>
#include <sstream>

int main() {
    std::string data = "apple,banana,carrot";
    std::stringstream ss(data);

    ss.ignore(6, ','); // 从流中跳过直到遇到逗号
    std::string fruit;
    ss >> fruit; // 读取跳过的部分之后的字符串

    std::cout << "Fruit after ignoring characters: " << fruit << std::endl;

    return 0;
}

// Fruit after ignoring characters: banana,carrot
```

```c++
#include <iostream>
#include <sstream>

int main() {
    std::string data = "apple,banana,carrot";
    std::stringstream ss(data);

    ss.ignore(20, ','); // 从流中跳过直到遇到逗号
    std::string fruit;
    ss >> fruit; // 读取跳过的部分之后的字符串

    std::cout << "Fruit after ignoring characters: " << fruit << std::endl;

    return 0;
}

//Fruit after ignoring characters: banana,carrot
```

#### 3.1.2 ignore(nCount)

**只指定数量**：`ignore(nCount)` 用于从流中跳过指定数量的字符。

```cpp
// 示例
stringstream ss("123456789");
ss.ignore(5);
int num;
ss >> num;
std::cout << "After ignoring 5 characters: " << num << std::endl;
```

#### 3.1.3 默认

在 C++ 中，`std::basic_istream` 类的 `ignore` 函数有几种重载形式，其中最常见的形式是 `ignore(streamsize n = 1, int_type delim = EOF)`。

- **n**：表示要忽略的字符数。默认情况下，它是1，表示忽略一个字符。
- **delim**：表示定界字符的整数值。当遇到这个字符时，`ignore` 操作会停止。`delim` 的默认值是 `EOF`，表示没有定界字符。这意味着在默认情况下，`ignore` 函数将忽略指定数量的字符，并继续直到流的末尾。

根据上述默认参数，如果您只使用 `ignore()` 调用而不提供参数，它将忽略流中的下一个字符，并继续直到流的末尾。

```c++
#include <iostream>
#include <sstream>

int main() {
    std::string data = "example";
    std::stringstream ss(data);

    char ch;
    ss.ignore(); // 忽略下一个字符

    while (ss >> ch) {
        std::cout << ch << std::endl;
    }

    return 0;
}
```

在这个示例中，`ss.ignore()` 表示忽略流中的下一个字符。在这种情况下，它将忽略字符 `'e'`，而后续的 `while` 循环将输出剩余的字符。

### 3.2 peek

在 C++ 中，`std::stringstream` 类提供了 `peek` 函数，它允许你查看流中的下一个字符，但不会将其提取出来。这通常用于在读取字符之前查看下一个字符，以决定接下来的操作。

```c++
#include <iostream>
#include <sstream>

int main() {
    std::string data = "Hello, World!";
    std::stringstream ss(data);

    char ch;

    ch = ss.peek();  // 查看下一个字符
    std::cout << "Peeked character: " << ch << std::endl;

    // 读取字符
    ss.get(ch);
    std::cout << "Read character: " << ch << std::endl;

    return 0;
}
```

### 3.3 putback

`putback` 是 `std::stringstream` 类的成员函数，用于将一个字符放回到流中，以便稍后能够重新读取。这个函数非常有用，因为它允许您在读取一个字符后，将其放回流中，以便在后续的操作中重新访问它。

```c++
#include <iostream>
#include <sstream>
#include <cctype>

int main() {
    std::string data = "Skip until a digit is found: abc 123 xyz";
    std::stringstream ss(data);

    char ch;
    while (ss.get(ch)) {
        if (std::isdigit(ch)) {
            ss.putback(ch);  // 将数字字符放回流中
            break;
        }
    }

    // 读取剩下的字符串
    std::string remaining;
    ss >> remaining;

    std::cout << "Remaining string after ignore: " << remaining << std::endl;

    return 0;
}
```

```c++
#include <iostream>
#include <sstream>

int main() {
    std::string data = "Hello, World!";
    std::stringstream ss(data);

    char ch;
    ss.get(ch);  // 读取第一个字符
    std::cout << "Read character: " << ch << std::endl;

    ss.putback(ch);  // 将刚刚读取的字符放回流中

    ss.get(ch);  // 再次读取字符
    std::cout << "Read character again: " << ch << std::endl;

    return 0;
}
```

