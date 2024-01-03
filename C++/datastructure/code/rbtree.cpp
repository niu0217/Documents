#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

enum Color {
    RED, BLACK
};

//红黑树的结点
struct RBTreeNode {
    Color color_;  //颜色
    int key_;  //值
    RBTreeNode* left_;  //左孩子
    RBTreeNode* right_;  //右孩子
    RBTreeNode* parent_;  //父亲
    RBTreeNode(int key)
        :color_(RED), key_(key), left_(nullptr), right_(nullptr), parent_(nullptr) { }
};

//红黑树
class RBTree {
public:
    RBTree(): root_(nullptr) { }
    ~RBTree();

    //操作函数
    void left_rotate(RBTreeNode* root);  //左旋函数
    void right_rotate(RBTreeNode* root); //右旋函数
    void insert(RBTreeNode* z);  //插入一个新结点

    //辅助函数
    void fixup(RBTreeNode* root);  //调整插入后的红黑树
    void mid_traversal(RBTreeNode* root);  //中序遍历
    void pre_traversal(RBTreeNode* root);  //先序遍历
    void delete_tree(RBTreeNode* root);  //删除树中的所有结点

public:
    RBTreeNode* root_;  //根结点
};

RBTree::~RBTree() {
    delete_tree(root_);
    printf("destructure...\n");
}

//左旋：
//  1.当前结点的右子树会作为新树的根结点
//  2.当前结点会作为新树的根结点的左子树
//  3.如果，新的树根，原来有左子树，原来的左子树，就作为旧根结点的右子树
void RBTree::left_rotate(RBTreeNode* root) {
    RBTreeNode* new_root = root->right_;  //对应步骤1
    RBTreeNode* root_rl = root->right_->left_;  //保存当前结点的右子树的左子树结点
    root->right_ = root_rl; //对应步骤3

    //修改父结点
    //一共三个结点的父结点改变了：root_rl,new_root,root
    //修改root_rl的父结点
    if(root_rl != nullptr) {
        root_rl->parent_ = root;
    }
    //修改new_root的父结点
    new_root->parent_ = root->parent_;
    if(root->parent_ == nullptr) {
        //说明，原来的root，就是整个树的根
        root_ = new_root;
    }
    else if(root == root->parent_->left_) {
        root->parent_->left_ = new_root;
    }
    else if(root == root->parent_->right_) {
        root->parent_->right_ = new_root;
    }
    //修改root的父结点
    new_root->left_ = root;  //对应步骤2
    root->parent_ = new_root;
}

//右旋：
//  1.当前结点的左子树会作为新树的根结点
//  2.当前结点会作为新树的根结点的右子树
//  3.如果，新的树根，原来有右子树，原来的右子树，就作为就根结点的左子树
void RBTree::right_rotate(RBTreeNode* root) {
    RBTreeNode* new_root = root->left_;  //对应步骤1
    RBTreeNode* root_lr = root->left_->right_;  //保存当前结点的左子树的右子树结点
    root->left_ = root_lr; //对应步骤3

    //修改父结点
    //一共三个结点的父结点改变了：root_lr,new_root,root
    //修改root_lr的父结点
    if(root_lr != nullptr) {
        root_lr->parent_ = root;
    }
    //修改new_root的父结点
    new_root->parent_ = root->parent_;
    if(root->parent_ == nullptr) {
        //说明，原来的root，就是整个树的根
        root_ = new_root;
    }
    else if(root == root->parent_->left_) {
        root->parent_->left_ = new_root;
    }
    else if(root == root->parent_->right_) {
        root->parent_->right_ = new_root;
    }
    //修改root的父结点
    new_root->right_ = root;  //对应步骤2
    root->parent_ = new_root;
}

//调整插入后的红黑树
void RBTree::fixup(RBTreeNode* u) {
    while((u->parent_ != nullptr) && (u->parent_->color_ == RED)) {
        if(u->parent_ == u->parent_->parent_->left_) {
            //LXx
            //获取插入结点的叔叔结点
            RBTreeNode* y = u->parent_->parent_->right_;
            if((y != nullptr) && (y->color_ == RED)) {
                //LXr
                //1.u的父亲结点变为黑色
                //2.u的叔叔结点变为黑色
                //3.u的祖父结点变为红色
                //4.将u更新为u的祖父结点，继续向上检查
                u->parent_->color_ = BLACK;
                y->color_ = BLACK;
                u->parent_->parent_->color_ = BLACK;
                u = u->parent_->parent_;
            }
            else if((y == nullptr) || (y->color_ == BLACK)) {
                if(u == u->parent_->right_) {
                    //LRb
                    //1.先转换为LLb型
                    //  1.pu更新为u
                    //  2.对u子树进行左旋
                    //2.u的父亲结点变为黑色
                    //3.u的祖父结点变为红色
                    //4.对u的祖父结点为根的子树进行右旋
                    u = u->parent_;
                    left_rotate(u);
                }
                //LLb
                //1.u的父亲结点变为黑色
                //2.u的祖父结点变为红色
                //3.对u的祖父结点为根的子树进行右旋
                u->parent_->color_ = BLACK;
                u->parent_->parent_->color_ = RED;
                right_rotate(u->parent_->parent_);
            }
        }
        else if(u->parent_ == u->parent_->parent_->right_) {
            //RXx
            //获取插入结点的叔叔结点
            RBTreeNode* y = u->parent_->parent_->left_;
            if((y != nullptr) && (y->color_ == RED)) {
                //RXr
                //1.u的父亲结点变为黑色
                //2.u的叔叔结点变为黑色
                //3.u的祖父结点变为红色
                //4.将u更新为u的祖父结点，继续向上检查
                u->parent_->color_ = BLACK;
                y->color_ = BLACK;
                u->parent_->parent_->color_ = RED;
                u = u->parent_->parent_;
            }
            else if((y == nullptr) || (y->color_ == BLACK)) {
                if(u == u->parent_->left_) {
                    //RLb
                    //1.先转换为RRb型
                    //  1.pu更新为u
                    //  2.对u子树进行右旋
                    //2.u的父亲结点变为黑色
                    //3.u的祖父结点变为红色
                    //4.对u的祖父结点为根的子树进行右旋
                    u = u->parent_;
                    right_rotate(u);
                }
                //RRb
                //1.u的父亲结点变为黑色
                //2.u的祖父结点变为红色
                //3.对u的祖父结点为根的子树进行左旋
                u->parent_->color_ = BLACK;
                u->parent_->parent_->color_ = RED;
                left_rotate(u->parent_->parent_);
            }
        }
    }
    root_->color_ = BLACK;
}

//插入一个新结点
void RBTree::insert(RBTreeNode* z) {
    RBTreeNode* y = nullptr;
    RBTreeNode* x = root_;
    while(x != nullptr) {
        y = x;  //y保存的是插入结点的父结点
        if(z->key_ < x->key_) {
            x = x->left_;
        }
        else if(z->key_ > x->key_) {
            x = x->right_;
        }
        else {
            return;  //不允许插入两个值相同的结点
        }
    }

    //找到z的父结点
    z->parent_ = y;
    if(y == nullptr) {
        //如果要插入这个位置的父结点是空，则说明是根结点
        root_ = z;
    }
    else if(z->key_ < y->key_) {
        y->left_ = z;
    }
    else if(z->key_ > y->key_) {
        y->right_ = z;
    }

    //调整红黑树
    fixup(z);
}

void RBTree::mid_traversal(RBTreeNode* root) {
    if(root == nullptr) {
        return;
    }
    mid_traversal(root->left_);
    printf("key:%d, color:%d\n", root->key_, root->color_);
    mid_traversal(root->right_);
}

void RBTree::pre_traversal(RBTreeNode* root) {
    if(root == nullptr) {
        return;
    }
    printf("key:%d, color:%d\n", root->key_, root->color_);
    pre_traversal(root->left_);
    pre_traversal(root->right_);
}

//采用后序遍历的方式删除所有结点
void RBTree::delete_tree(RBTreeNode* root) {
    if(root == nullptr) {
        return;
    }
    delete_tree(root->left_);
    delete_tree(root->right_);
    delete root;
    printf("destructure...\n");
}

int main()
{
    vector<int> key_vec = {
        10, 50, 60, 62, 65, 70
    };
    RBTree* rbtree = new RBTree();
    RBTreeNode* node;
    for(auto key: key_vec) {
        node = new RBTreeNode(key);
        rbtree->insert(node);
        node = nullptr; //防止悬挂指针的产生
    }
    //打印插入的结点的结果
    printf("-----------------------中序遍历---------------------\n");
    rbtree->mid_traversal(rbtree->root_);
    printf("-----------------------先序遍历---------------------\n");
    rbtree->pre_traversal(rbtree->root_);

    //释放内存。防止内存泄漏
    delete rbtree;
}
