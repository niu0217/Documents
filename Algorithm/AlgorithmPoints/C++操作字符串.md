# C++操作字符串

## 引入

在 C++ 中，标准库 `string` 类提供了许多可用于处理字符串的常用函数。以下是一些常见的 `std::string` 类的成员函数及其功能描述：

1. **length() / size()**:
   - 返回字符串的长度。
2. **substr(pos, len)**:
   - 从字符串中提取子串，从位置 `pos` 开始，最多包括 `len` 个字符。
3. **find(str, pos)** / **rfind(str, pos)**:
   - 在字符串中查找子串 `str`，并返回第一次出现的位置（`find`），或者最后一次出现的位置（`rfind`）。
   - 可以指定起始搜索位置 `pos`。
4. **compare(str)** / **compare(pos1, len1, str)** / **compare(pos1, len1, str, pos2, len2)**:
   - 将字符串与 `str` 进行比较。
   - 也可以通过指定位置和长度来比较子串。
5. **replace(pos, len, str)** / **replace(iterator1, iterator2, str)**:
   - 用字符串 `str` 替换从位置 `pos` 开始的 `len` 个字符（第一种形式），或者指定迭代器范围的字符串（第二种形式）。
6. **erase(pos, len)** / **erase(iterator)** / **erase(iterator1, iterator2)**:
   - 从位置 `pos` 开始删除 `len` 个字符（第一种形式），或者指定迭代器范围的字符（第二种形式）。
   - 也可以使用迭代器来删除单个字符（第二种形式）。
7. **c_str()** / **data()**:
   - 返回一个以 null 结尾的 C 风格字符串。
8. **empty()**:
   - 判断字符串是否为空。
9. **append(str)** / **append(str, pos, len)** / **append(n, ch)**:
   - 在字符串末尾追加字符串 `str`。
   - 也可以追加 `str` 的子串或重复添加字符 `ch`。
10. **push_back(ch)**:
    - 在字符串末尾添加一个字符。
11. **pop_back()**:
    - 删除字符串末尾的字符。
12. **at(pos)** / **operator[]**:
    - 访问指定位置的字符。

这些函数只是 `std::string` 类中可用函数的一小部分。C++ 标准库还提供了许多其他在字符串处理中有用的函数和算法。

## 1. 字符串替换

在 C++ 中，您可以使用 `std::string` 类中的 `replace` 函数来进行字符串替换。这个函数允许您使用新的字符串替换指定位置的字符或字符串。

以下是 `std::string::replace` 函数的主要形式：

```cpp
string& replace( size_type pos1, size_type n1, const string& str );
```

这个函数接受三个参数：

- **pos1**：开始替换的位置。
- **n1**：要替换的字符数。
- **str**：用于替换的字符串。

以下是使用 `replace` 函数进行字符串替换的示例：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "This is a test string.";
    
    // 从第 10 个字符开始，替换 4 个字符为 "example"
    str.replace(10, 4, "example");
    
    std::cout << str << std::endl;  // 输出 "This is a example string."

    return 0;
}
```

在这个示例中，我们使用 `replace` 函数从第 10 个字符开始，替换 4 个字符为 "example"。

除了上述形式之外，`std::string` 类还提供了其他形式的 `replace` 函数，以满足不同的替换需求，包括根据迭代器范围进行替换等。

## 2. 字符串查找

`std::string` 的 `find` 函数用于在字符串中查找子字符串，返回第一次出现该子字符串的位置。以下是该函数的签名：

```cpp
size_t find(const std::string& str, size_t pos = 0) const noexcept;
```

- **str**：要搜索的子字符串。
- **pos**：起始搜索位置，默认为0。

该函数返回匹配子字符串的第一个字符的位置，如果未找到匹配项，则返回 `std::string::npos`。

示例代码如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "example string to search";
    std::string substr = "string";

    size_t found = str.find(substr);
    if (found != std::string::npos) {
        std::cout << "Substring found at position: " << found << std::endl;
    } else {
        std::cout << "Substring not found" << std::endl;
    }

    return 0;
}
```

在上面这个示例中，`find` 函数被用来查找子字符串 "string" 在 "example string to search" 中的位置。

除了上述形式，`find` 函数还有其他重载形式，可以接受单个字符或者 C 风格字符串作为搜索目标，并且可以指定搜索起始位置和搜索方向（向前或向后）。

## 3. 字符串截取

在 C++ 中，可以使用 `std::string` 类的 `substr` 成员函数来截取子字符串。`substr` 函数接受起始位置和要截取的子字符串长度作为参数，并返回一个新的 `std::string` 对象，其中包含从指定位置开始的指定长度的字符。

以下是 `substr` 函数的基本签名：

```cpp
std::string substr(size_t pos = 0, size_t len = npos) const;
```

- **pos**：起始位置，默认为 0。
- **len**：要截取的字符数，默认为 `std::string::npos`，表示截取直到字符串末尾。

示例代码如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "This is a test string";
    
    // 从位置 5 开始截取长度为 2 的子字符串
    std::string sub = str.substr(5, 2);
    std::cout << "Subtring: " << sub << std::endl;  // 输出 "is"

    // 从位置 5 开始截取到末尾的子字符串
    std::string sub2 = str.substr(5);
    std::cout << "Subtring2: " << sub2 << std::endl;  // 输出 "is a test string"

    return 0;
}
```

在这个示例中，使用了 `substr` 函数来分别截取指定位置和长度的子字符串，以及从指定位置截取到末尾的子字符串。

这些特性使得 `substr` 成员函数非常灵活，方便地对字符串进行截取操作。

## 4. 字符串删除

在 C++ 中，可以使用 `std::string` 类的 `erase` 成员函数来删除字符串中的字符或子字符串。`erase` 函数有多个重载形式，可以用于删除单个字符、一段范围内的字符，或者用于删除指定位置和长度的子字符串。

以下是 `erase` 函数的基本签名：

```cpp
std::string& erase(size_t pos = 0, size_t len = npos);
```

- **pos**：要删除的起始位置，默认为 0。
- **len**：要删除的字符数，默认为 `std::string::npos`，表示删除直到字符串末尾。

示例代码如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "This is a test string";

    // 删除从位置 5 开始的 2 个字符
    str.erase(5, 2); 
    std::cout << "Erased string: " << str << std::endl;  // 输出 "This a test string"

    return 0;
}
```

在这个示例中，使用了 `erase` 函数来删除指定位置和长度的子字符串。

另外，`erase` 函数还有其他几个重载的形式，比如可以使用迭代器来删除字符或子字符串。

## 5. 字符串添加

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";

    // 在末尾添加字符串
    str.append(" world");
    std::cout << str << std::endl;  //Hello world

    // 在末尾添加部分子字符串
    str.append(" of C++", 3, 2);  // 从 "of C++" 的第三个位置开始，添加 2 个字符
    std::cout << str << std::endl;  //Hello world C

    // 在末尾重复添加字符
    str.append(3, '!');  // 添加 3 个感叹号
    std::cout << str << std::endl;  // Hello world C!!!

    return 0;
}
```

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";

    // 使用 += 操作符添加字符串
    str += " world";
    std::cout << str << std::endl;  // 输出 "Hello world"

    return 0;
}
```

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";

    // 在位置5插入字符串
    str.insert(5, " world");
    std::cout << str << std::endl;  // 输出 "Hello world"

    // 在位置6插入重复字符
    str.insert(6, 3, '!');
    std::cout << str << std::endl;  // 输出 Hello !!!world

    return 0;
}
```

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, how are you?";

    // 替换 "how are you" 部分的内容
    str.replace(7, 11, "world");
    std::cout << str << std::endl;  // 输出 "Hello, world?"

    return 0;
}
```

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";

    // 向字符串末尾添加单个字符
    str.push_back('!');
    std::cout << str << std::endl;  // 输出 "Hello!"

    return 0;
}
```

