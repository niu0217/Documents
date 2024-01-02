#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<stack>
#include<climits>
#include<fstream>
#include<sstream>  //用于处理字符串流
#include<string>
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

    //操作二叉树
    void delete_tree(TreeNode* root);  //删除二叉树的所有节点
    TreeNode* delete_node(TreeNode* root, int key);  //删除二叉树中的一个节点

    //辅助函数
    TreeNode* left_rotate(TreeNode* root);  //左旋函数
    TreeNode* right_rotate(TreeNode* root); //右旋函数
    TreeNode* adjust_tree(TreeNode* root, int flags);  //调整插入或者删除结点后的树
    int get_height(TreeNode* root);  //取得树的高度
    int get_balance(TreeNode* root);  //取得树的平衡因子
    TreeNode* get_minvalue_node(TreeNode* root);  //取得最小值节点
    TreeNode* search_node(TreeNode* root, int key);  //递归查找节点

public:
    TreeNode* root_;  //树的根节点
};

BinaryTree::~BinaryTree() {
    delete_tree(root_);
    printf("destructure.......\n");
}

//插入新结点：
//  1.找到结点的位置并插入
//  2.调整树使其平衡
TreeNode* BinaryTree::insert(TreeNode* root, int value) {
    //步骤1
    if(root == nullptr) {
        return new TreeNode(value);  //中
    }
    if(value < root->value_) {
        root->left_ = insert(root->left_, value);  //左
    }
    else if(value > root->value_) {
        root->right_ = insert(root->right_, value);  //右
    }
    else {
        return root;  //不运行插入相同的结点
    }

    //步骤2
    return adjust_tree(root, 0);
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

//删除一个结点：
//  1.找到删除的结点并删除
//  2.调整树使其平衡
TreeNode* BinaryTree::delete_node(TreeNode* root, int key) {
    //步骤1
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

    //步骤2
    return adjust_tree(root, 1);
}

//左旋：
//  1.当前结点的右子树会作为新树的根结点
//  2.当前结点会作为新树的根结点的左子树
//  3.如果，新的树根，原来有左子树，原来的左子树，就作为旧根结点的右子树
TreeNode* BinaryTree::left_rotate(TreeNode* root) {
    TreeNode* new_root = root->right_;  //对应步骤1
    TreeNode* root_rl = root->right_->left_;  //保存当前结点的右子树的左子树结点
    new_root->left_ = root;  //对应步骤2
    root->right_ = root_rl;  //对应步骤3
    return new_root;  //将新根结点返回
}

//右旋：
//  1.当前结点的左子树会作为新树的根结点
//  2.当前结点会作为新树的根结点的右子树
//  3.如果，新的树根，原来有右子树，原来的右子树，就作为就根结点的左子树
TreeNode* BinaryTree::right_rotate(TreeNode* root) {
    TreeNode* new_root = root->left_;  //对应步骤1
    TreeNode* root_lr = root->left_->right_;  //保存当前结点的左子树的右子树结点
    new_root->right_ = root;  //对应步骤2
    root->left_ = root_lr;  //对应步骤3
    return new_root;  //将新根结点返回
}

//调整树，使其平衡
//  flags: 为0代表插入结点的调整；为1代表删除结点的调整
TreeNode* BinaryTree::adjust_tree(TreeNode* root, int flags) {
    int balance = get_balance(root);  //取得当前结点的平衡因子
    int left_balance = get_balance(root->left_);  //取得当前结点的左子树的平衡因子
    int right_balance = get_balance(root->right_);  //取得当前结点的右子树的平衡因子
    //我们是否调整这个树，是看平衡因子是不是绝对值大于1
    //LL型失衡
    bool condition;  //用于区别插入和删除结点时的不同处理条件
    if(flags == 1) {
        condition = left_balance >= 0;
    }
    else {
        condition = left_balance > 0;
    }
    if(balance > 1 && condition) {
        return right_rotate(root);  //当前结点右旋一次
    }
    //LR型失衡
    if(balance > 1 && left_balance < 0) {
        root->left_ = left_rotate(root->left_);  //当前结点的左子树进行一次左旋
        //此时已经变成了LL型失衡
        return right_rotate(root);  //当前结点进行一次右旋即可
    }
    //RR型失衡
    if(flags == 1) {
        condition = right_balance <= 0;
    }
    else {
        condition = right_balance < 0;
    }
    if(balance < -1 && condition) {
        return left_rotate(root);  //当前结点进行一次左旋
    }
    //RL型失衡
    if(balance < -1 && right_balance > 0) {
        root->right_ = right_rotate(root->right_);  //当前结点的右子树进行一次右旋
        //此时已经变成了RR型失衡
        return left_rotate(root);  //当前结点进行一次左旋即可
    }
    return root;  //树本来就是平衡的，则不做处理
}

//递归然后计算树的高度
int BinaryTree::get_height(TreeNode* root) {
    if(root == nullptr) {
        return 0;  //空树的树高为0
    }
    int left_subtree_height = get_height(root->left_);
    int right_subtree_height = get_height(root->right_);
    //+1是加上根节点的树高1
    return 1 + max(left_subtree_height, right_subtree_height);
}

//树的平衡因子：左子树高度-右子树高度
int BinaryTree::get_balance(TreeNode* root) {
    if(root == nullptr) {
        return 0;
    }
    return get_height(root->left_) - get_height(root->right_);
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

//测试所有的插入删除结点的情况
void test_insert_delete() {
    vector<BinaryTree*> tree_vec;

    //从文件中读取数据，并用来构建二叉树
    ifstream infile("avltree_data.txt");  //创建一个文件对象，用来读取数据
    if(!infile.is_open()) {
        cerr<<"Unable to open file avltree_data.txt"<<endl;
        return;
    }
    string line;  //用于逐行读取的字符串
    while(getline(infile, line)) { //逐行读取文件
        istringstream iss(line);  //将每行内容放入字符串流中
        string token;
        BinaryTree* tree = new BinaryTree();
        iss>>token;  //读取每行的第一个词
        if(token == "I") {
            int value;
            while(iss>>value) {  //从字符串流中读取值
                tree->root_ = tree->insert(tree->root_, value);
            }
            tree_vec.push_back(tree);
        }
    }
    infile.close();  //关闭文件

    //打印构建的二叉树
    for(auto tree: tree_vec) {
        print_tree(tree->root_);
        printf("\n\n");
    }

    tree_vec[4]->root_ = tree_vec[4]->delete_node(tree_vec[4]->root_, 4);
    print_tree(tree_vec[4]->root_);

    //释放内存
    for(auto tree: tree_vec) {
        delete tree;
        tree = nullptr;
    }
}

int main()
{
    test_insert_delete();

    printf("\n\n");
}

