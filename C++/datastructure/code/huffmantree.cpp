#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<sstream>

using namespace std;

//哈夫曼树的节点结构体
struct Node {
    char ch;  //字符
    int weight;  //权值
    Node* left;  //左子树
    Node* right; //右子树
    Node(char c, int w, Node* l = nullptr, Node* r = nullptr)
        :ch(c), weight(w), left(l), right(r) { }
};

//比较函数，用于优先队列中的排序
struct Compare {
    bool operator()(const Node* l, const Node* r) {
        return l->weight > r->weight;  //最小堆，权值小的优先级高
    }
};

//哈夫曼类
class HuffmanTree {
public:
    HuffmanTree(): root(nullptr) {}
    ~HuffmanTree() {
        clear(root);
    }

    //构建哈夫曼树
    Node* build_huffmantree(const map<char, int> huff_data_map) {
        priority_queue<Node*, vector<Node*>, Compare> minheap_pq;  //最小堆优先队列
        for(auto& data : huff_data_map) {
            minheap_pq.push(new Node(data.first, data.second));
        }
        //当优先队列中还有多于一个节点时，继续构建树
        while(minheap_pq.size() > 1) {
            Node* left = minheap_pq.top();  //取出权值最小的节点作为左子树
            minheap_pq.pop();
            Node* right = minheap_pq.top(); //取出下一个权值最小的节点作为右子树
            minheap_pq.pop();
            int sum = left->weight + right->weight;
            minheap_pq.push(new Node(0, sum, left, right)); //0代表这是一个非叶子节点
        }
        Node* root = minheap_pq.top();
        minheap_pq.pop();
        return root;
    }

    //生成哈夫曼编码(前缀编码)
    void generate_huffmancodes(Node* root, string code, map<char, string>& huffman_codes_map) const {
        if(root == nullptr) {
            return;
        }
        if(root->ch != 0) {  //非叶子节点
            huffman_codes_map[root->ch] = code;
        }
        else { //叶子节点
            generate_huffmancodes(root->left, code + "0", huffman_codes_map);
            generate_huffmancodes(root->right, code + "1", huffman_codes_map);
        }
    }

    //释放内存，防止内存泄漏
    void clear(Node* root) {
        if(root == nullptr) {
            return;
        }
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;  //防止悬挂指针问题
        cout<<"destructure....\n";
    }
public:
    Node* root;  //哈夫曼树的根节点
};

int main()
{
    map<char, int> huff_data_map = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };
    HuffmanTree* huffman_tree = new HuffmanTree();  //创建哈夫曼树对象
    huffman_tree->root = huffman_tree->build_huffmantree(huff_data_map); //构建哈夫曼树
    map<char, string> huffman_codes_map;  //用于存储哈夫曼编码的map
    huffman_tree->generate_huffmancodes(huffman_tree->root, "", huffman_codes_map);
    for(auto& data : huffman_codes_map) {
        cout<<data.first<<": "<<data.second<<endl;
    }

    //手动释放申请的内存
    delete huffman_tree;
}

