#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<stack>
#include<climits>
using namespace std;

//二叉树节点的定义
struct TreeNode {
    int value_;
    TreeNode* left_;
    TreeNode* right_;
    TreeNode(int val): value_(val), left_(nullptr), right_(nullptr) { }
};

//二叉树类的定义
class BinaryTree {
public:
    BinaryTree(): root_(nullptr) {}
    ~BinaryTree();

    //创建二叉树
    TreeNode* insert(TreeNode* root, int value);  //一个一个节点的创建

    //遍历二叉树
    void preorder_traversal_recursive(TreeNode* root);  //前序遍历(递归)
    void inorder_traversal_recursive(TreeNode* root);  //中序遍历(递归)
    void postorder_traversal_recursive(TreeNode* root);  //后序遍历(递归)
    void preorder_traversal(TreeNode* root);  //前序遍历
    void inorder_traversal(TreeNode* root);  //中序遍历
    void postorder_traversal(TreeNode* root);  //后序遍历
    void levelorder_traversal(TreeNode* root);  //层次遍历

    //操作二叉树
    void delete_tree(TreeNode* root);  //删除二叉树的所有节点
    TreeNode* delete_node(TreeNode* root, int key);  //删除二叉树中的一个节点
    TreeNode* get_minvalue_node(TreeNode* root);  //取得最小值节点
    TreeNode* search_node(TreeNode* root, int key);  //递归查找节点

public:
    TreeNode* root_;  //树的根节点
};

BinaryTree::~BinaryTree() {
    delete_tree(root_);
}

TreeNode* BinaryTree::insert(TreeNode* root, int value) {
    if(root == nullptr) {
        return new TreeNode(value);  //中
    }
    if(value <= root->value_) {
        root->left_ = insert(root->left_, value);  //左
    }
    if(value > root->value_) {
        root->right_ = insert(root->right_, value);  //右
    }
    return root;
}

void BinaryTree::preorder_traversal_recursive(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    printf("%d ", root->value_);  //中
    preorder_traversal_recursive(root->left_);  //左
    preorder_traversal_recursive(root->right_);  //右
}

void BinaryTree::inorder_traversal_recursive(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    inorder_traversal_recursive(root->left_);  //左
    printf("%d ", root->value_);  //中
    inorder_traversal_recursive(root->right_);  //右
}

void BinaryTree::postorder_traversal_recursive(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    postorder_traversal_recursive(root->left_);  //左
    postorder_traversal_recursive(root->right_);  //右
    printf("%d ", root->value_);  //中
}

void BinaryTree::preorder_traversal(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    std::stack<TreeNode*> node_stack;
    node_stack.push(root);
    while(!node_stack.empty()) {
        TreeNode* node = node_stack.top();
        node_stack.pop();
        printf("%d ", node->value_);
        //先放右节点，这样才能保证左节点先被访问
        if(node->right_) {
            node_stack.push(node->right_);
        }
        if(node->left_) {
            node_stack.push(node->left_);
        }
    }
}

void BinaryTree::inorder_traversal(TreeNode* root) {
    std::stack<TreeNode*> node_stack;
    TreeNode* cur_node = root;
    while(cur_node != nullptr || !node_stack.empty()) {
        //先将左子树所有节点入栈，直到左子树为空
        while(cur_node != nullptr) {
            node_stack.push(cur_node);
            cur_node = cur_node->left_;
        }
        //此时栈顶元素就是当前需要访问的节点
        cur_node = node_stack.top();
        node_stack.pop();
        printf("%d ", cur_node->value_);
        cur_node = cur_node->right_;
    }
}

void BinaryTree::postorder_traversal(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    std::stack<TreeNode*> node_stack_in;
    std::stack<TreeNode*> node_stack_out;
    node_stack_in.push(root);
    while(!node_stack_in.empty()) {
        TreeNode* node = node_stack_in.top();
        node_stack_in.pop();
        node_stack_out.push(node);  //放入栈中用于输出
        if(node->left_) {
            node_stack_in.push(node->left_);
        }
        if(node->right_) {
            node_stack_in.push(node->right_);
        }
    }
    //此时node_stack_out中保存的就是后序遍历的顺序
    //弹出栈即可
    while(!node_stack_out.empty()) {
        printf("%d ", node_stack_out.top()->value_);
        node_stack_out.pop();
    }
}

void BinaryTree::levelorder_traversal(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    std::queue<TreeNode*> node_queue;
    node_queue.push(root);
    while(!node_queue.empty()) {
        int size = node_queue.size();
        for(int i = 0; i < size; i++) {
            TreeNode* node = node_queue.front();
            node_queue.pop();
            printf("%d ", node->value_);
            if(node->left_) {
                node_queue.push(node->left_);
            }
            if(node->right_) {
                node_queue.push(node->right_);
            }
        }
    }
}

//采用后序遍历（递归）的方式确保每个节点的内存都被释放了
void BinaryTree::delete_tree(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    delete_tree(root->left_);
    delete_tree(root->right_);
    delete root;
    root = nullptr;  //置空避免悬挂指针
}

TreeNode* BinaryTree::delete_node(TreeNode* root, int key) {
    if(root == nullptr) {
        return root;  //没找到直接返回
    }
    if(key < root->value_) {
        //在左子树中删除，并且用root->left_接住删除后的左子树的根节点
        root->left_ = delete_node(root->left_, key);
    }
    else if(key > root->value_) {
        //在右子树中删除，并且用root->right_接住删除后的右子树的根节点
        root->right_ = delete_node(root->right_, key);
    }
    else {
        //找到要删除的节点
        if(root->left_ == nullptr) {  //只有一个右节点或者没有子节点
            TreeNode* after_delete_subtree = root->right_;
            delete root;
            return after_delete_subtree;
        }
        else if(root->right_ == nullptr) {  //只有一个左节点或者没有子节点
            TreeNode* after_delete_subtree = root->left_;
            delete root;
            return after_delete_subtree;
        }
        else {  //有两个子节点，获取右子树中的最小值节点来替换当前节点，并删除那个最小值节点
            TreeNode* min_subtree_node = get_minvalue_node(root->right_);
            root->value_ = min_subtree_node->value_;
            root->right_ = delete_node(root->right_, min_subtree_node->value_);
        }
    }
    return root;  //返回修改后的根指针（可能是新的根）
}

//获取最小值节点（总是位于左子树的最末端）
TreeNode* BinaryTree::get_minvalue_node(TreeNode* root) {
    TreeNode* cur_node = root;
    while(cur_node && cur_node->left_) {
        cur_node = cur_node->left_;
    }
    return cur_node;
}

//采用中序遍历（递归）的方式查找节点
TreeNode* BinaryTree::search_node(TreeNode* root, int key) {
    if(root == nullptr || root->value_ == key) {
        return root;
    }
    if(key < root->value_) {
        return search_node(root->left_, key);
    }
    else if(key > root->value_) {
        return search_node(root->right_, key);
    }
    return nullptr;  //永远到不了这里
}


//打印二叉树
void print_tree(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    std::queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
        int count = que.size();
        for(int i = 0; i < count; i++) {
            TreeNode* node = que.front();
            que.pop();
            printf("%d ", node->value_);
            if(node->left_) {
                que.push(node->left_);
            }
            if(node->right_) {
                que.push(node->right_);
            }
        }
        printf("\n");
    }
}

//测试几种创建二叉树的方式
void test_create_tree() {
    //方式一
    BinaryTree tree1;
    tree1.root_ = new TreeNode(1);
    tree1.root_->left_ = new TreeNode(2);
    tree1.root_->right_ = new TreeNode(3);
    tree1.root_->left_->left_ = new TreeNode(4);
    tree1.root_->left_->right_ = new TreeNode(5);
    print_tree(tree1.root_);

    //方式二
    BinaryTree bst_tree;
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 5);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 3);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 7);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 2);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 4);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 6);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 8);
    print_tree(bst_tree.root_);
}

//测试二叉树的遍历
void test_traversal() {
    //创建二叉树
    BinaryTree bst_tree;
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 5);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 3);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 7);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 2);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 4);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 6);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 8);
    print_tree(bst_tree.root_);
    printf("\n");

    printf("前序遍历：\n");
    bst_tree.preorder_traversal_recursive(bst_tree.root_);
    printf("\n");
    bst_tree.preorder_traversal(bst_tree.root_);
    printf("\n\n");

    printf("中序遍历：\n");
    bst_tree.inorder_traversal_recursive(bst_tree.root_);
    printf("\n");
    bst_tree.inorder_traversal(bst_tree.root_);
    printf("\n\n");

    printf("后序遍历：\n");
    bst_tree.postorder_traversal_recursive(bst_tree.root_);
    printf("\n");
    bst_tree.postorder_traversal(bst_tree.root_);
    printf("\n\n");

    printf("层次遍历：\n");
    bst_tree.levelorder_traversal(bst_tree.root_);
    printf("\n\n");
}

//测试常见的树操作
void test_operator_function() {
    //创建二叉树
    BinaryTree bst_tree;
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 5);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 3);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 7);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 2);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 4);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 6);
    bst_tree.root_ = bst_tree.insert(bst_tree.root_, 8);
    print_tree(bst_tree.root_);
    printf("\n");

    //查找树节点
    int key = 22;
    printf("Find：%d\n", key);
    TreeNode* node = bst_tree.search_node(bst_tree.root_, key);
    if(node == nullptr) {
        printf("Not find...\n\n");
    }
    else {
        printf("Find it...\n\n");
    }

    //输出最小节点的值
    node = bst_tree.get_minvalue_node(bst_tree.root_);
    printf("Min value is %d\n", node->value_);

    //删除二叉树中的一个节点
    key = 2;
    printf("二叉树本来的样子：\n");
    print_tree(bst_tree.root_);
    printf("\n\n");
    printf("删除节点：%d\n", key);
    printf("二叉树删除后的样子：\n");
    bst_tree.root_ = bst_tree.delete_node(bst_tree.root_, key);
    print_tree(bst_tree.root_);
    printf("\n\n");
}

int main()
{
    // test_create_tree();
    // test_traversal();
    test_operator_function();
}

