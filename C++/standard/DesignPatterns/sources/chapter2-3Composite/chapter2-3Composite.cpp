#include <iostream>
#include <list>
#include <string>
//接口：不管是商品还是盒子，都依赖这个接口
class OrderNode {
protected:
    OrderNode* m_parent;
    float m_price;
public:
    virtual ~OrderNode(){}
    OrderNode() :m_parent(nullptr), m_price(0.0f) {

    }
    OrderNode(OrderNode* parent,float price) :m_parent(parent), m_price(price) {

    }
    void setParent(OrderNode* node) { m_parent = node; }
    OrderNode* getParent() { return m_parent; }
    virtual bool isComposite() const { return false; }
    //Add, Remove

    void setPrice(float price) { m_price = price; }
    float getPrice() { return m_price; }
    virtual std::string operation() = 0;
};
//产品
class Product :public OrderNode {
public:
    ~Product(){}
    Product(float price):OrderNode(nullptr,price){}
    virtual std::string operation()override{
        return "产品";
    };
};
//盒子
class Box :public OrderNode {
protected:
    std::list<OrderNode*> m_children;
public:
    ~Box() {}
    Box(){}
    bool isComposite() const override{
        return true;
    }
    void Add(OrderNode* node) {
        m_children.push_back(node);
        node->setParent(this);
        m_price += node->getPrice();
    }
    void Remove(OrderNode* node) {
        m_children.remove(node);//注意：只是从容器里移除。
        node->setParent(nullptr);
        m_price -= node->getPrice();
    }
    virtual std::string operation()override {
        std::string result;
        m_price = 0;
        for (auto c : m_children) {
            if (c == m_children.back()) {
                result += c->operation();
            }
            else {
                result += c->operation()+'+';
            }
            m_price += c->getPrice();
        }
        return "盒子（"+result+")";
    };
};
void clientCode(OrderNode* node) {
    std::cout << "结构:" << node->operation() << std::endl;
    std::cout << "价格:" << node->getPrice();
}
int main()
{
    std::cout << "#处理叶子节点.....\n";
    Product leaf(5.0f);
    clientCode(&leaf);

    std::cout << "\n\n";
    std::cout << "#处理组合节点.....\n";
    Box tree;
    Box branch1;
    Box branch2;
    Product leaf_1(5.0f);
    Product leaf_2(5.0f);
    Product leaf_3(5.0f);
    tree.Add(&branch1);
    tree.Add(&branch2);
    branch1.Add(&leaf_1);
    branch1.Add(&leaf_2);
    branch2.Add(&leaf_3);
    clientCode(&tree);
    std::cout << "\n\n";
    tree.Add(&leaf);
    clientCode(&tree);
    std::cout << "\n\n";
}

