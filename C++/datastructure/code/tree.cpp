#include<iostream>

struct TreeNode {
    int value_;
    TreeNode* left_;
    TreeNode* right_;
    TreeNode(int val): value_(val), left_(nullptr), right_(nullptr) { }
};

class BinaryTree {
public:
    BinaryTree(): root_(nullptr) { }
    ~BinaryTree();

    //操作二叉树
    void clear();  //删除所有节点
    void insert(int value);  //插入节点
    void inorder_traversal() const;  //中序遍历

    //辅助函数
    void clear_helper(TreeNode* root);  //递归删除所有节点
    void insert_helper(TreeNode* root, int value);  //递归插入节点到合适的位置
    void inorder_traversal_helper(TreeNode* root) const;  //递归进行中序遍历

private:
    TreeNode* root_;
};

BinaryTree::~BinaryTree() {
    clear();
}

void BinaryTree::clear() {
    clear_helper(root_);
    root_ = nullptr;
}

void BinaryTree::insert(int value) {
    if(root_ == nullptr) {
        root_ = new TreeNode(value);
    }
    else {
        insert_helper(root_, value);
    }
}

void BinaryTree::inorder_traversal() const {
    inorder_traversal_helper(root_);
    printf("\n");
}

//采用后序遍历（递归）的方式删除所有节点
void BinaryTree::clear_helper(TreeNode* root) {
    if(root == nullptr) {
        return;
    }
    clear_helper(root->left_);
    clear_helper(root->right_);
    delete root;
    root = nullptr;  //置空避免悬挂指针
}

void BinaryTree::insert_helper(TreeNode* root, int value) {
    if(value < root->value_) {
        if(root->left_ == nullptr) {
            root->left_ = new TreeNode(value);
        }
        else {
            insert_helper(root->left_, value);
        }
    }
    else if(value > root->value_) {
        if(root->right_ == nullptr) {
            root->right_ = new TreeNode(value);
        }
        else {
            insert_helper(root->right_, value);
        }
    }
    else {
        //值相同时不做处理，不允许这种情况
        //根据设计自己调整
    }
}

void BinaryTree::inorder_traversal_helper(TreeNode* root) const {
    if(root != nullptr) {
        inorder_traversal_helper(root->left_);
        printf("%d ", root->value_);
        inorder_traversal_helper(root->right_);
    }
}

int main()
{
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.inorder_traversal();
}
