#include <iostream>

class Chair {
public:
    virtual ~Chair(){}
    virtual void sitOn() const = 0;
};
class ModernChair:public Chair {
public:
    virtual ~ModernChair() {}
    virtual void sitOn() const override {
        std::cout << "可以被坐下的ModernChair\n";
    }
};
class ChineseChair :public Chair {
public:
    virtual ~ChineseChair() {}
    virtual void sitOn() const override {
        std::cout << "可以被坐下的ChineseChair\n";
    }
};

class Table {
public:
    virtual ~Table() {}
    virtual void putOn() const = 0;
};
class ModernTable :public Table {
public:
    virtual ~ModernTable() {}
    virtual void putOn() const override {
        std::cout << "ModernTable可以放东西\n";
    }
};
class ChineseTable :public Table {
public:
    virtual ~ChineseTable() {}
    virtual void putOn() const override {
        std::cout << "ChineseTable可以放东西\n";
    }
};
class FurnitureFacotry {//抽象工厂
public:
    virtual Chair* createChair() const = 0;
    virtual Table* createTable() const = 0;
};
class ModernStyleFactory:public FurnitureFacotry {
public:
    virtual Chair* createChair() const override{
        return new ModernChair();
    }
    virtual Table* createTable() const override {
        return new ModernTable();
    }
};
class ChineseStyleFactory :public FurnitureFacotry {
public:
    virtual Chair* createChair() const override {
        return new ChineseChair();
    }
    virtual Table* createTable() const override {
        return new ChineseTable();
    }
};
class Client {
private:
    FurnitureFacotry* m_factory;
public:
    Client(FurnitureFacotry* factory){
        setFacotry(factory);
    }
    void buyFurniture() {
        Chair* chair = m_factory->createChair();
        Table* table = m_factory->createTable();
        chair->sitOn();
        table->putOn();
        delete chair;
        delete table;
    }

    void setFacotry(FurnitureFacotry* factory) {
        m_factory = factory;
    }
};
int main()
{
    ModernStyleFactory modernFactory;
    Client client(&modernFactory);
    client.buyFurniture();

    ChineseStyleFactory chineseFactory;
    client.setFacotry(&chineseFactory);
    client.buyFurniture();
}
