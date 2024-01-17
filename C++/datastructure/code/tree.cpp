#include<iostream>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val): value(val), left(nullptr), right(nullptr) { }
};

class BinaryTree {
public:
    BinaryTree(): root(nullptr) { }
    ~BinaryTree() {
        deleteAllNode();
    }

    void deleteAllNode();
    void deleteAllNodeHelper(TreeNode* toDeleteRoot);
    void insertNode(int value);
    void insertNodeHelper(TreeNode* rootOfTree, int value);
    void midorderTraversal() const;
    void midorderTraversalHelper(TreeNode* rootOfTree) const;
private:
    TreeNode* root;
};

void BinaryTree::deleteAllNode() {
    deleteAllNodeHelper(root);
    root = nullptr;
}

void BinaryTree::deleteAllNodeHelper(TreeNode* toDeleteRoot) {
    if(toDeleteRoot == nullptr) {
        return;
    }
    deleteAllNodeHelper(toDeleteRoot->left);
    deleteAllNodeHelper(toDeleteRoot->right);
    delete toDeleteRoot;
    toDeleteRoot = nullptr;  //置空避免悬挂指针
}

void BinaryTree::insertNode(int value) {
    if(root == nullptr) {
        root = new TreeNode(value);
    }
    else {
        insertNodeHelper(root, value);
    }
}

void BinaryTree::insertNodeHelper(TreeNode* rootOfTree, int value) {
    if(value < rootOfTree->value) {
        if(rootOfTree->left == nullptr) {
            rootOfTree->left = new TreeNode(value);
        }
        else {
            insertNodeHelper(rootOfTree->left, value);
        }
    }
    else if(value > rootOfTree->value) {
        if(rootOfTree->right == nullptr) {
            rootOfTree->right = new TreeNode(value);
        }
        else {
            insertNodeHelper(rootOfTree->right, value);
        }
    }
    else {
        //值相同时不做处理，不允许这种情况
        //根据设计自己调整
    }
}

void BinaryTree::midorderTraversal() const {
    midorderTraversalHelper(root);
    printf("\n");
}

void BinaryTree::midorderTraversalHelper(TreeNode* rootOfTree) const {
    if(rootOfTree != nullptr) {
        midorderTraversalHelper(rootOfTree->left);
        printf("%d ", rootOfTree->value);
        midorderTraversalHelper(rootOfTree->right);
    }
}

int main()
{
    BinaryTree* tree = new BinaryTree();
    tree->insertNode(5);
    tree->insertNode(3);
    tree->insertNode(7);
    tree->insertNode(2);
    tree->insertNode(4);
    tree->insertNode(6);
    tree->insertNode(8);
    tree->midorderTraversal();

    delete tree;
    tree = nullptr;
}

