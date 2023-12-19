# C++规范代码示例

## 漂亮的命名

### 文件命名

```
http_server_logs.h
my_class.cpp
wrap_python.hpp
floating_point_comparison_impl.hpp
```

### 函数命名

```
AddTableEntry()
DeleteUrl()
OpenFileOrDie()


my_exciting_member_variable()
set_my_exciting_member_variable()
```

个人倾向于：

`my_exciting_member_variable()`
`set_my_exciting_member_variable()`

### 类型命名

```c++
// 类和结构体
class UrlTable { ...
class UrlTableTester { ...
struct UrlTableProperties { ...

// 类型定义
typedef hash_map<UrlTableProperties *, string> PropertiesMap;

// using 别名
using PropertiesMap = hash_map<UrlTableProperties *, string>;

// 枚举
enum UrlTableErrors { ...
```

### 变量命名

```c++
//普通变量命名
string table_name;  // 好 - 用下划线.
string tablename;   // 好 - 全小写.
int num_dns_connections;   // 人人都知道 "DNS" 是什么
```

```c++
// 类数据成员变量命名
class TableInfo {
  ...
 private:
  string table_name_;  // 好 - 后加下划线.
  string tablename_;   // 好.
  static Pool<TableInfo>* pool_;  // 好.
};
```

```c++
// 结构体成员变量命名
struct UrlTableProperties {
  string name; //好
  int num_entries;  //好
  static Pool<UrlTableProperties>* pool; //好
};
```

### 常量命名

```c++
const int kDaysInAWeek = 7; //k开头，然后后面的首字母大写
```

### 枚举命名

```c++
enum UrlTableErrors {
    kOK = 0, 
    kErrorOutOfMemory,  //k开头，然后后面的首字母大写
    kErrorMalformedInput,
};
enum AlternateUrlTableErrors {
    OK = 0,
    OUT_OF_MEMORY = 1, //全部大写，_分隔
    MALFORMED_INPUT = 2,
};
```

### 宏命名

```c++
#define ROUND(x) ...
#define PI_ROUNDED 3.0
```

### 命名空间命名

```
websearch::index
websearch::util
```

