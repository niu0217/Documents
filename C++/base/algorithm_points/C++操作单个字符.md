# C++操作单个字符

## 1. 判断一个字符是否为字母

```c++
#include <iostream>
#include <cctype>

int main() {
    char ch = 'A';
    if (std::isalpha(ch)) {
        std::cout << ch << " is an alphabetic character." << std::endl;
    } else {
        std::cout << ch << " is not an alphabetic character." << std::endl;
    }
    return 0;
}
```

## 2. 判断一个字符是否是数字

```c++
#include <iostream>
#include <cctype>

int main() {
    char ch = '7';
    if (std::isdigit(ch)) {
        std::cout << ch << " is a digit." << std::endl;
    } else {
        std::cout << ch << " is not a digit." << std::endl;
    }
    return 0;
}
```

## 3. 判断一个字符是否是数字或字母

```c++
#include <iostream>
#include <cctype>

int main() {
    char ch1 = 'A';
    if (std::isalnum(ch1)) {
        std::cout << ch1 << " is an alphanumeric character." << std::endl;
    } else {
        std::cout << ch1 << " is not an alphanumeric character." << std::endl;
    }

    char ch2 = '7';
    if (std::isalnum(ch2)) {
        std::cout << ch2 << " is an alphanumeric character." << std::endl;
    } else {
        std::cout << ch2 << " is not an alphanumeric character." << std::endl;
    }

    char ch3 = '$';
    if (std::isalnum(ch3)) {
        std::cout << ch3 << " is an alphanumeric character." << std::endl;
    } else {
        std::cout << ch3 << " is not an alphanumeric character." << std::endl;
    }

    return 0;
}
```

