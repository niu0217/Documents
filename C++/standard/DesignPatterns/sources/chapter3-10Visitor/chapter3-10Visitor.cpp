#include <iostream>
#include <vector>
#include <string>

class IceCream;
class Popsicle;

class Visitor {
public:
    virtual void visitIceCream(const IceCream* element) const = 0;
    virtual void visitPopsicle(const Popsicle* element) const = 0;
};

class Component {
public:
    virtual void accept(Visitor* visitor) const =0;
};

class IceCream :public Component {
public:
    virtual void accept(Visitor* visitor) const {
        visitor->visitIceCream(this);
    }
    std::string getIceCream() const {
        return "冰激凌";
    }
};

class Popsicle :public Component {
public:
    virtual void accept(Visitor* visitor) const {
        visitor->visitPopsicle(this);
    }
    std::string getPopsicle() const {
        return "雪糕";
    }
};

class Frosting :public Visitor {
public:
    virtual void visitIceCream(const IceCream* element) const {
        std::cout << element->getIceCream() << "+糖霜\n";
    }
    virtual void visitPopsicle(const Popsicle* element) const {
        std::cout << element->getPopsicle() << "+糖霜\n";
    }
};

class Chocolate :public Visitor {
public:
    virtual void visitIceCream(const IceCream* element) const {
        std::cout << element->getIceCream() << "+巧克力\n";
    }
    virtual void visitPopsicle(const Popsicle* element) const {
        std::cout << element->getPopsicle() << "+巧克力\n";
    }
};

void clintCode(std::vector<Component*> components, Visitor* visitor) {
    for (auto item : components) {
        item->accept(visitor);
    }
}
int main()
{
    std::vector<Component*> components = { new IceCream,new Popsicle,new Popsicle };
    Frosting frosting;
    clintCode(components, &frosting);
    std::cout << std::endl;
    Chocolate chocolate;
    clintCode(components, &chocolate);
    for (auto item : components) {
        delete item;
    }
}