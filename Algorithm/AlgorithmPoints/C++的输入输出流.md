# C++的输入输出流

## 1. 引入

cerr、clog、cout都可以用于输出。区别是，如果你将要输出一条错误提示信息，就可以用cerr来输出，准确来说，cerr和clog是为了增加可读性，让标识更明显。

+ cout：标准输出，可以文件重定向
+ cerr：标准错误，不能文件重定向
+ clog：标准错误，可以文件重定向
+ cin：标准输入

流对象常用的处理函数：

+ 输出字符：`put()`
+ 输入字符：`get()`
+ 输出字符串：`write()`
+ 输入字符串：`getline()`

重点：`cin.get()`可以把`cin`理解为屏幕的输入，这段代码表示需要你从键盘上输入东西，此时`get()`表示从键盘输入流中（即你在控制台输入的东西）获取内容。

## 2. 实战代码

### 2.1 代码一：使用cin和cout

```c++
#include<iostream>
#include<string>

using namespace std;

int main()
{
    int x;
    int y;
    cout<<"X: ";
    //开始时键盘输入的数据在缓冲区中，遇到换行符时将数据写入到x中
    cin>>x;
    cout<<"Y: ";
    cin>>y;

    cout<<"result of x and y:\n";
    //开始时输出的数据在缓冲区中，遇到换行符 ｜ flush | endl时刷新到输出设备上（终端）
    cout<<x<<endl;
    cout<<y<<endl;
}
```

### 2.2 代码二：使用getline

```c++
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//getline的结束条件：直到遇到换行符或者到达文件末尾或者遇到自己定义的分割符

//从标准输入获取一行并输出
void method1() {
    string line;
    getline(cin, line); //遇到换行符结束
    cout << "You entered: " << line << endl;
}

//从文件流获取一行
void method2() {
    //file是一个文件输入流
    ifstream file("example.txt");
    string line;
  	//到达文件末尾结束
    while(getline(file, line)) {
        cout<<line<<endl;
    }
    file.close();
}

//指定定界符作为输入结束条件
void method3() {
    string inputStr;
    char delimiter = '$';
    getline(cin, inputStr, delimiter);
    cout<<"Input until '$': "<<inputStr<<endl;
}

//从字符串流获取一行
void method4() {
    string inputStr = "Hello, this is a test string";
    string word;
    //stream是一个字符串输入流
    istringstream stream(inputStr);
    while(getline(stream, word, ' ')) {
        cout<<word<<endl;
    }
}

int main() {
    // method1();
    // method2();
    // method3();
    method4();
}
```

### 2.3 代码三：使用write

```c++
#include <iostream>
#include <fstream>
using namespace std;

//将整数数组以二进制形式写入文件
void method1() {
    ofstream outFile("data.bin", ios::out | ios::binary);
    if (outFile.is_open()) {
        int data[] = {10, 20, 30, 40, 50};
        outFile.write(reinterpret_cast<const char*>(data), sizeof(data));
        outFile.close();
        cout << "Binary data was written to file." << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

//写入字符串到文件
void method2() {
    ofstream outFile("text_data.txt", ios::out | ios::app);
    if (outFile.is_open()) {
        string text = "Hello, this is a text file.";
        outFile.write(text.c_str(), text.size());
        outFile.write(text.c_str(), text.size());
        outFile.write(text.c_str(), text.size());
        outFile.close();
        cout << "Text data was written to file." << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

int main() {
    // method1();
    method2();
}
```

### 2.4 代码四：使用get

```c++
#include <iostream>
using namespace std;

//从标准输入读取单个字符
void method1() {
    char ch;
    cout<<"Enter a character: ";
    cin.get(ch);
    cout<<"You entered: "<<ch<<endl;
}

//读取至换行符并存储在字符串中
void method2() {
    char str[255];
    cout<<"Enter a sentence: ";
    cin.get(str, 255, '\n');
    cout<<"Your entered: "<<str<<endl;
}

//读取一行并处理每个字符
void method3() {
    char c;
    cout<<"Enter a sentence: ";
    while(cin.get(c)) {
        if(c == '\n') {
            break;
        }
        else {
            cout<<"Read: "<<c<<endl;
        }
    }
}

//读取固定长度的字符序列
void method4() {
    char str[6]; // 5个字符 + 1个用于存储null终止符
    cout << "Enter 5 characters: ";
    cin.get(str, 6);
    cout << "You entered: " << str << endl;
}

int main()
{
    // method1();
    // method2();
    // method3();
    method4();
}
```

### 2.5 代码五：使用put

```c++
#include <iostream>
#include <fstream>
using namespace std;

//输出单个字符到标准输出
void method1() {
    char ch = 'A';
    cout.put(ch);
}

//输出单个字符到文件
void method2() {
    ofstream outFile("output.txt");
    char ch = 'B';
    if (outFile.is_open()) {
        outFile.put(ch);
        outFile.close();
    }
}

//输出多个字符到标准输出
void method3() {
    char str[] = "Hello, world!";
    cout.write(str, 13); // 13是字符串长度
}

int main() {
    // method1();
    method3();
}
```

## 3. 解释

### 3.1 C++中的cin

在C++中，`std::cin`是标准输入流对象，用于从标准输入设备（通常是键盘）读取输入。下面是关于`std::cin`的一些重要信息和原理：

1. **标准输入**：`std::cin`对应于标准输入，它是一个全局的 `std::istream` 类型的对象。可以用于从用户键盘输入获取数据。
2. **输入操作符**：通常与`std::cin`一起使用的是输入操作符 `>>`，用于从标准输入中读取数据并将其存储到变量中。例如：`int number; std::cin >> number;`
3. **缓冲区**：输入操作时，`std::cin`会将数据存储在输入缓冲区中，直到换行符出现。一旦遇到换行符，`std::cin`会将数据从缓冲区读取出来，并使其可供程序使用。如果需要连续输入，可以使用 `std::getline` 或多次使用输入操作符 `>>`。
4. **数据类型转换**：`std::cin`可以将输入的字符串转换为特定的数据类型，例如将用户输入的字符串转换成整数、浮点数等。如果输入无法转换成指定的数据类型，输入操作将失败，并且`std::cin`的状态会被设置为失败状态，这时需要进行错误处理。
5. **错误状态**：`std::cin`具有状态标志，表示输入操作是否成功。当遇到错误时，可以通过检查`std::cin`的状态标志来进行错误处理。

以上就是`std::cin`的一些基本原理和工作方式。它是C++中用于从标准输入设备接收用户输入的重要组件。

### 3.2 C++中的cout

在C++中，`std::cout`被用作标准输出流，它负责将数据输出到标准输出设备（通常是显示器）。以下是关于`std::cout`的一些重要信息和工作原理：

1. **标准输出**：`std::cout`对应于标准输出，它是一个全局的 `std::ostream` 类型的对象。可以用于将数据输出到控制台或其他标准输出设备。
2. **输出操作符**：`std::cout`通常与输出操作符 `<<` 一起使用，用于将数据输出到标准输出设备。例如：`int number = 10; std::cout << "The number is: " << number;`
3. **数据流**：`std::cout`使用输出流的模式，可以连续使用输出操作符 `<<` 将多个数据项一起输出到标准输出设备。
4. **数据类型转换**：`std::cout`能够将不同类型的数据转换成可显示的形式。例如，当输出一个整数时，`std::cout`会自动将它转换为字符串并输出。
5. **格式化输出**：除了简单输出外，`std::cout`还支持格式化输出，比如控制输出的精度、宽度、对齐方式等。
6. **缓冲区**：与`std::cin`类似，`std::cout`也有一个输出缓冲区，数据首先被存储在缓冲区中，然后定期刷新到输出设备上。刷新缓冲区的时机可以是程序结束时、遇到换行符时，或显式调用 `std::flush` 或 `std::endl`。

总的来说，`std::cout`是C++中用于将数据输出到标准输出设备的重要组件。它允许程序员以简单和灵活的方式将所需信息输出到屏幕上，是C++标准库中常用的一部分。

### 3.3 C++中的getline

在C++中，`std::getline`是用于从输入流中读取一行文本的函数。其基本原理如下：

```C++
#include <iostream>
#include <string>

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::cout << "You entered: " << line << std::endl;
    return 0;
}
```

在上述示例中，`std::getline`从 `std::cin` 读取一行输入，并将其存储到变量 `line` 中。这个函数会一直读取输入，直到遇到换行符（包括换行符）为止。获得的输入存储在字符串 `line` 中，之后可以对其进行处理或输出。

`std::getline()` 函数的原理包括以下方面：

1. 接受输入流和字符串作为参数：`std::getline`接受输入流（比如 `std::cin`）和用于存储输入行的字符串作为参数。
2. 从输入流中读取输入：它从输入流中读取字符，直到遇到换行符为止。
3. 存储输入内容：读取的内容会被存储在提供的字符串中，直到遇到换行符或者到达文件末尾。
4. 丢弃换行符：换行符在被读取后会被丢弃，并不会被存储到输出的字符串中。

因此，`std::getline`函数可以让你从输入流中获得一行文本，而不用担心输入中的换行符。

### 3.4 C++中的write

在 C++ 中，`write()` 是 `ostream` 类型的成员函数之一，它用于将二进制数据写入到输出流中。这个函数可以用于向文件或标准输出流写入二进制数据。下面是一个简单的示例，演示了如何使用 `write()` 函数：

```c++
#include <iostream>
#include <fstream>

int main() {
  	//文件输出流：file
    std::ofstream file("binary_data.dat", std::ios::out | std::ios::binary);
    if (file.is_open()) {
        int data[] = {10, 20, 30, 40, 50};

        // 将整数数组写入到文件中
        file.write(reinterpret_cast<const char*>(data), sizeof(data));

        file.close();
        std::cout << "Binary data was written to file." << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    return 0;
}
```

在这个示例中，我们打开一个名为 "binary_data.dat" 的文件，以二进制模式进行写操作。`write()` 函数被用来将整数数组写入文件中。需要注意的是，我们使用 `reinterpret_cast` 将整数数组的地址转换为 `const char*` 类型，以便将其以二进制形式写入文件。

总的来说，`write()` 是一个用于将二进制数据写入输出流（比如文件流）的非常有用的函数。

### 3.5 C++中的get

在 C++ 中，`get` 是 `istream` 类型的成员函数之一，用于从输入流中读取单个字符（包括空格和换行符）。其基本原型如下：

```C++
istream& get ( char& c );
istream& get ( char* s, streamsize n, char delim );
istream& get ( char* s, streamsize n );
```

这些函数的作用如下：

1. `get (char& c)`：从输入流中读取下一个字符，并将其存储到变量 `c` 中。
2. `get (char* s, streamsize n, char delim)`：从输入流中读取字符，存储到数组 `s` 中，最多读取 `n-1` 个字符，或者直到遇到定界符 `delim`（不包括定界符）。
3. `get (char* s, streamsize n)`：从输入流中读取字符，存储到数组 `s` 中，最多读取 `n-1` 个字符。

下面是一个简单的示例，演示了如何使用 `get` 函数：

```c++
#include <iostream>
using namespace std;

int main() {
   char ch, str[255];

   cout << "Enter a sentence: ";
   cin.get(ch);
   cout << "You entered: " << ch << endl;

   cin.get(str, 255);
   cout << "You entered: " << str << endl;

   return 0;
}
```

在这个示例中，首先使用 `get` 函数读取单个字符，然后使用另一种形式的 `get` 函数读取整行输入到字符数组中。

总的来说，`get` 函数是用于从输入流中获取字符或字符数组的成员函数，能够让你以多种不同方式从输入中获取数据。

### 3.6 C++中的put

在 C++ 中，`put` 是用于向输出流中写入单个字符的成员函数，属于 `ostream` 的一部分。它允许将一个字符写入到输出流，通常用于输出单个字符到文件或标准输出。以下是一个简单的示例，演示了如何使用 `put` 函数：

```c++
#include <iostream>
using namespace std;

int main() {
   char ch = 'A';
   
   // 输出一个字符到标准输出
   cout.put(ch);

   // 输出一个字符到文件
   ofstream outFile("output.txt");
   if(outFile.is_open()) {
      outFile.put(ch);
      outFile.close();
   }

   return 0;
}
```

在这个示例中，首先使用 `cout.put(ch)` 将字符 `'A'` 写入到标准输出。然后，通过创建一个文件输出流，并使用 `outFile.put(ch)` 将字符写入到文件 "output.txt" 中。

总的来说，`put` 函数是用于将单个字符写入输出流的成员函数，可以在标准输出或文件输出流中使用。