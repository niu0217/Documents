#include <iostream>
#include <vector>
#include <string>
//产品1
class SimpleHouse{
public:
    std::vector<std::string> m_parts;
    void printParts() const {
        std::cout << "SimpleHouse 包括：\n";
        for (int i = 0; i < m_parts.size(); ++i) {
            std::cout << m_parts[i] << std::endl;
        }
        std::cout << "----------------------\n";
    }
};

class Builder {
public:
    virtual ~Builder(){}
    virtual void reset() = 0;
    virtual void makeBaseHouse() = 0;
    virtual void makeGarage() = 0;
    virtual void makePool() = 0;
};
//concreteBuilder1，施工队
class SimpleHouseBuilder:public Builder {
private:
    SimpleHouse* m_simplehouse;
public:
    SimpleHouseBuilder() {
        reset();
    }
    ~SimpleHouseBuilder() { delete m_simplehouse; }
    void reset() override{
        m_simplehouse = new SimpleHouse();
    }
    virtual void makeBaseHouse() override{
        m_simplehouse->m_parts.push_back("BaseHouse");
    }
    virtual void makeGarage() override {
        m_simplehouse->m_parts.push_back("Garage");
    }
    virtual void makePool() override {
        m_simplehouse->m_parts.push_back("Pool");
    }

    SimpleHouse* getResult() {
        SimpleHouse* result = m_simplehouse;
        reset();
        return result;
    }
};
//主管：负责流程
class Director {
private:
    Builder* m_builder;
public:
    void setBuilder(Builder* builder) {
        m_builder = builder;
    }
    void makeSimpleHouse() {
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
    }
    void makeFullFuncHouse() {
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
        m_builder->makePool();
    }
};
void client(Director* director) {
    std::cout << "客户自己设计流程：---------------------\n";
    SimpleHouseBuilder* builder = new SimpleHouseBuilder();
    builder->makeBaseHouse();
    builder->makeGarage();
    SimpleHouse * simpleHouse= builder->getResult();
    simpleHouse->printParts();
    delete simpleHouse;
    std::cout << "主管负责设计流程：---------------------\n";
    director->setBuilder(builder);
    director->makeFullFuncHouse();
    simpleHouse = builder->getResult();
    simpleHouse->printParts();
    delete simpleHouse;
    delete builder;
}
int main()
{
    Director director;
    client(&director);

}
