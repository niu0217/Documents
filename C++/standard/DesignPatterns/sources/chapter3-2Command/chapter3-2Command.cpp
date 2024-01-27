#include <iostream>
#include <string>
#include <vector>
//Receiver
class Kitchen {
private:
    Kitchen(){}
public:
    static Kitchen* getInstance() {
        static Kitchen* instance = new Kitchen();
        return instance;
    }

    void prepareFood(const std::string& food) {
        std::cout << "厨房：正在准备(" << food << ".)\n";
    }
};
//
class Command {
public:
    virtual ~Command(){}
    virtual void execute() const = 0;
};
//ConcreteCommand1
class Order :public Command {
private:
    Kitchen* m_kitchen;//receiver
    std::vector<std::string> m_foods;//params
public:
    Order(Kitchen* kitchen, std::vector<std::string> foods) 
    :m_kitchen(kitchen),m_foods(foods){

    }
    virtual ~Order() {}
    virtual void execute() const override {
        std::cout << "订单：需要厨房进行处理...\n";
        for (const std::string& item : m_foods) {
            m_kitchen->prepareFood(item);
        }     
    }
};
//Invoker
class Waitress {
private:
    Command* m_command;
public:
    ~Waitress() { delete m_command; }

    void orderUp(Command* command) {
        std::cout << "服务员：...提交订单...\n";
        m_command = command;//用于回收内存
        m_command->execute();
    }
};
//
class Client {
public:
    void orderFood(Waitress& waitress, std::vector<std::string> foods) {
        waitress.orderUp(new Order(Kitchen::getInstance(),foods));
    }
};
int main()
{
    Client Arxibye;
    Waitress waitress;//Invoker
    Arxibye.orderFood(waitress, { "波士顿大龙虾","炒刀削","雪顶咖啡" });
}
