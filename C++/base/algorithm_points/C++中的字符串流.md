# C++中的字符串流

## 引入

C++ 中的字符串流（stringstream）是一种特殊的流，它允许你像使用标准流一样使用字符串。字符串流可以让你将字符串当作流来处理，你可以向其输入数据，然后从中读取数据。这在某些情况下非常有用，比如将不同类型的数据组合成一个字符串，或者从字符串中提取各种类型的数据。

下面是一些使用字符串流的示例：

### 将数据写入字符串流

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

### 从字符串流中读取数据

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

## 举例

### istringstream (输入字符串流)

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

### ostringstream (输出字符串流)

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