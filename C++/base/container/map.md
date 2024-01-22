# map

## 1. 问题

## 2. 引入代码

```c++
#include <iostream>
#include <map>

int main() {
    // 初始化一个map，键为int类型，值为string类型
    std::map<int, std::string> myMap;

    // 增：插入元素
    myMap.insert(std::make_pair(1, "Apple"));
    myMap.insert(std::make_pair(2, "Banana"));
    myMap.insert(std::make_pair(3, "Cherry"));

    // 查：通过键查找值
    if (myMap.find(2) != myMap.end()) {
        std::cout << "Found value for key 2: " << myMap[2] << std::endl;
    } else {
        std::cout << "Key 2 not found." << std::endl;
    }

    // 改：通过插入相同键的新值来覆盖旧值
    myMap.insert(std::make_pair(2, "Blueberry")); // "Banana"被"Blueberry"覆盖

    // 查：再次查找修改后的值
    if (myMap.find(2) != myMap.end()) {
        std::cout << "Updated value for key 2: " << myMap[2] << std::endl;
    } else {
        std::cout << "Key 2 not found." << std::endl;
    }

    // 删：删除键值对
    myMap.erase(1);

    // 遍历map
    for (const auto& entry : myMap) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    }

    // 清空map
    myMap.clear();

    // 检查map是否为空
    if (myMap.empty()) {
        std::cout << "Map is empty." << std::endl;
    } else {
        std::cout << "Map is not empty." << std::endl;
    }

    return 0;
}

```

这个示例中涵盖了以下map操作：

- `insert`：插入键值对。
- `find`：通过键查找值。
- 通过插入相同键的新值来覆盖旧值。
- `erase`：删除特定键的键值对。
- 范围-based for循环遍历map。
- `clear`：清空map。
- `empty`：检查map是否为空。

## 3. 原理

https://blog.csdn.net/qq_21989927/article/details/108068998

https://21xrx.com/Articles/read_article/128825

C++ Map是用于存储键值对的关联式容器，常常被用于实现高效率的查找和数据更新。它的底层实现原理是关键算法中的红黑树，这种数据结构具有结构简单、插入/删除效率高以及查询效率高等特点。

首先，C++ Map底层实现采用了二叉搜索树的数据结构，它是一种由节点组成的非线性结构，每个节点都有着左、右两个子节点，子节点的值要么比父节点小、要么比父节点大。红黑树是一种特殊的二叉搜索树，它的每个节点要么是红色，要么是黑色。并且，它需要满足以下5个特性：

1. 每个节点是红色或黑色。
2. 根节点是黑色。
3. 每个叶子节点（NIL节点，最后一个空节点）是黑色的。
4. 如果一个节点是红色的，则它的两个子节点都是黑色的。
5. 对于任意节点，从该节点到其每个子孙节点的所有路径上包含相同数目的黑色节点。

红黑树的这些特性保证了它的平衡性和高效性。在插入和删除操作时，根据红黑树的定义，它会通过旋转、颜色翻转等方式来保证树的平衡。而在查找操作时，红黑树能够快速定位节点。

C++ Map底层实现红黑树的插入操作需要分为以下几步：

1. 将插入节点按照二叉搜索树的方式插入到红黑树中。
2. 将新节点的颜色设置为红色。
3. 根据红黑树的特性，递归地调整红黑树的结构，保证树的平衡性。

C++ Map底层实现红黑树的删除操作需要分为以下几步：

1. 在树中找到要删除的节点，并且记录它的父节点、子节点、兄弟节点等信息。
2. 根据要删除节点的情况，考虑可能涉及的四种子情况，并用相应的操作将节点删除。
3. 根据红黑树的特性，递归地调整红黑树的结构，保证树的平衡性。

总之，C++ Map底层实现以红黑树为基础，实现了高效率的增删查操作。了解Map的底层实现原理，能够帮助我们更好地使用这个容器，同时也让我们能够更好地理解其他容器的实现原理。

## 4. 优点和缺点

C++中`std::map`的优点：

1. **自动排序**：`std::map`中的元素总是按照键的升序排列，无需手动排序。
2. **高效查找**：通过键进行查找的时间复杂度为O(log n)，这是因为`std::map`底层通常采用红黑树实现，这是一种自平衡二叉搜索树。
3. **键唯一性**：确保了键值对的键是唯一的，适用于需要根据唯一标识符（键）快速查找关联数据（值）的场景。
4. **迭代器稳定性**：除了被删除或插入位置的迭代器之外，其他迭代器在插入和删除操作后通常保持有效。
5. **范围查询**：支持高效的区间查询，如使用`lower_bound`、`upper_bound`和`equal_range`函数。
6. **内存管理**：自动管理内存，无需担心动态分配和释放问题。

缺点：

1. **空间开销**：每个节点都需要存储键、值、左右子节点指针以及颜色信息，相较于不考虑顺序的数据结构（如哈希表），空间效率较低。
2. **插入和删除成本较高**：尽管平均时间复杂度为O(log n)，但在最坏情况下仍然可能达到O(log n)。相对于基于哈希表的`unordered_map`，插入和删除操作速度可能较慢。
3. **无随机访问**：无法像数组那样通过索引直接访问特定位置的元素。
4. **初始化和复制成本**：创建一个新的map或者复制一个现有的map时，需要遍历所有元素，因此时间复杂度为O(n)。
5. **哈希表性能优势缺失**：当不需要有序性或仅关注查找性能时，基于哈希表的容器（如`unordered_map`）可能提供更快的查找速度（理想情况下为O(1)）。

## 5. 增删查改效率

在C++中，`std::map`的底层实现通常基于红黑树（Red-Black Tree），这是一种自平衡二叉搜索树。因此，其增删查改操作的效率如下：

1. **查找（Search）**：
   - 查找操作的时间复杂度为O(log n)，其中n是map中的元素数量。由于键值对在map中按键排序，所以可以使用二分查找法快速定位。
2. **插入（Insertion）**：
   - 插入操作的时间复杂度也是O(log n)。新插入的元素需要被放置在正确的位置以维持有序性，这涉及到在树中找到合适位置并进行必要的结构调整以保持红黑树性质。
3. **修改（Modification）**：
   - 修改一个已存在的键对应的值不需要移动节点，时间复杂度为O(1)。但请注意，`std::map`没有直接提供通过索引修改值的方法，而是通过键来访问和修改对应的值。
4. **删除（Deletion）**：
   - 删除操作的时间复杂度同样是O(log n)。首先需要找到要删除的键值对，然后执行删除操作，并可能需要重新调整树结构以保持红黑树性质。

综上所述，`std::map`提供了稳定且高效的增删查改操作，尤其适用于需要数据有序排列并且允许快速查找、插入和删除的情况。然而，相比基于哈希表的关联容器如`unordered_map`，在大规模数据集上的平均性能可能会稍逊一筹，因为哈希表在理想情况下可以提供O(1)的查找、插入和删除时间复杂度。

## 6. 常用函数

```
begin()         返回指向map头部的迭代器
clear(）        删除所有元素
count()         返回指定元素出现的次数
empty()         如果map为空则返回true
end()           返回指向map末尾的迭代器
equal_range()   返回特殊条目的迭代器对
erase()         删除一个元素，参数可以是迭代器，可以是关键字
find()          查找一个元素，返回迭代器
get_allocator() 返回map的配置器
insert()        插入元素，插入pair
key_comp()      返回比较元素key的函数
lower_bound()   返回键值>=给定元素的第一个位置
max_size()      返回可以容纳的最大元素个数
rbegin()        返回一个指向map尾部的逆向迭代器
rend()          返回一个指向map头部的逆向迭代器
size()          返回map中元素的个数
swap()           交换两个map
upper_bound()    返回键值>给定元素的第一个位置
value_comp()     返回比较元素value的函数
```

## 7. 补充代码

### 7.1 简单使用

```c++
#include<iostream>
#include<string>
#include<map>
 
using namespace std;
 
int main(){  
    map<string,int> s;   //map定义 
    map<string,int>::iterator it;   //迭代器 
     
    //插入元素的三种方法 
    s.insert(make_pair("Amey",99));
    s.insert(pair<string,int>("Maroon",100));
    s["Tom"]=88;
    
    //查找的两种方法 count和find 
    cout<<s.count("Tom")<<endl;  
    it=s.find("Thm");
	  if (it==s.end()) cout<<"No"<<endl;
		else cout<<it->first<<"  "<<it->second<<endl;
	
    //删除的两种方法	
    s.erase("Tom");
    it=s.find("Amey");
    s.erase(it);
 
    //迭代器遍历方法 
    for(it=s.begin(); it!= s.end(); it++){ 
        cout<<it->first<<"  "<<it->second<<endl;
    }
}
```

插入：

+ 用insert函数插入数据，在数据的插入上涉及到集合的唯一性这个概念，即当map中有这个关键字时，insert操作是插入不了的数据，但是用数组方式就不同了，它可以覆盖以前该关键字对应的值。

查找：

+ 用count函数来判定关键字是否出现，其缺点是无法定位数据出现位置,由于map的特性一对一的映射关系，就决定了count函数的返回值只有两个，要么是0，要么是1，出现的情况，当然是返回1了。

+ 用find函数来定位数据出现位置，它返回的一个迭代器，当数据出现时，它返回数据所在位置的迭代器，如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器。传入的参数是要查找的key。

### 7.2  自定义map

从大到小排序：

```c++
map<string,int, greater<string> > s;   //map定义 
map<string,int, greater<string> >::iterator it;   //迭代器 
```

结构体map：

```c++
#include<iostream>
#include<string>
#include<map>
 
using namespace std;
 
struct sdu{
	int math,chi,sin;
};
 
int main(){  
    map<string,sdu > s;   //map定义 
    map<string,sdu >::iterator it;   //迭代器 
     
    sdu a;  a.math=100;  a.chi=98;  a.sin=20;
    
    s.insert(make_pair("Amey",a));
    //s.insert(pair<string,int>("Maroon",100));
    s["Tom"].math=88; s["Tom"].chi=100; s["Tom"].sin=85;
    
   	//迭代器遍历方法 
    for(it=s.begin(); it!= s.end(); it++){ 
        cout<<it->first<<" "<<s[it->first].math<<" "<<s[it->first].chi<<" "<<s[it->first].sin<<endl;
    }
}
```

重载小于操作符：

```c++
#include <map>
#include <iostream>
 
using namespace std;
 
struct  sdu{
	int x;
	int y;
	bool operator < (const sdu &o) const{ 
		return x < o.x || y < o.y;
	}
};
 
int main(){ 
	map<sdu,string> s;
	sdu a={ 1, 2 };  s[a] = "abc";
	a={ 6, 5 };  s[a] = "ss";
	a={ 4, 100 };  s[a] = "pp";
	map<sdu, string>::iterator it;
	for (it = s.begin(); it != s.end();it++){
		cout << it->first.x << " " << it->first.y << " " << it->second << std::endl;
	}
}
```

