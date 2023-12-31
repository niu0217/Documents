# 汇编-C++类

## 1. 案例一

代码：

```c++
#include<iostream>
#include<vector>

struct TreeNode {
    int value_;
    TreeNode* left_;
    TreeNode* right_;
    TreeNode(int value) {
        value_ = value;
        left_ = nullptr;
        right_ = nullptr;
    }
};

int main()
{
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);

    node1->left_ = node2;
    node1->right_ = node3;
    return 0;
}
```

分析：

