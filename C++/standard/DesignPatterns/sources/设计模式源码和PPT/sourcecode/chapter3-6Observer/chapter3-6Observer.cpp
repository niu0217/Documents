#include <iostream>
#include <string>
#include <list>

class IObserver {
public:
    virtual void update(const std::string& messageFromSubject) = 0;
};

class ISubject {
public:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};

class Mate50 :public ISubject {
private:
    std::list<IObserver*> m_observerList;
    std::string m_message;
public:
    virtual void attach(IObserver* observer) override{
        m_observerList.push_back(observer);
    }

    virtual void detach(IObserver* observer)override {
        m_observerList.remove(observer);
    }
    virtual void notify() override {
        std::list<IObserver*>::iterator iter = m_observerList.begin();
        while (iter != m_observerList.end()) {
            (*iter++)->update(m_message);
        }
    }

    void createMessage(std::string message = "") {
        m_message = message;
        notify();
    }
};

class Customer :public IObserver {
private:
    ISubject* m_mate50;
    std::string m_messageFromMate50;
    int m_numer;
    static int m_staticNumber;
public:
    Customer(ISubject* subject) :m_mate50(subject) {
        m_mate50->attach(this);
        std::cout << "我是\"" << ++Customer::m_staticNumber << "\"号订购者。\n";
        m_numer = Customer::m_staticNumber;
    }
    void update(const std::string& messageFromSubject) override {
        m_messageFromMate50 = messageFromSubject;
        printInfo();
    }
    void printInfo() {
        std::cout << "\"" << m_numer << "\"号订购者：接收到新的消息："
           <<m_messageFromMate50<<"\n";
    }
    void removeFromList() {
        m_mate50->detach(this);
        std::cout << "\"" << m_numer << "\"号订购者：从列表中移除。\n";
    }
};
int Customer::m_staticNumber=0;
int main()
{
    Mate50* mate50 = new Mate50();
    Customer* c1 = new Customer(mate50);
    Customer* c2 = new Customer(mate50);
    Customer* c3 = new Customer(mate50);
    Customer* c4;
    Customer* c5;
    mate50->createMessage("Mate50即将到店......");
    c4= new Customer(mate50);
    mate50->createMessage("Mate50明天到店......");
    c5 = new Customer(mate50);
    c2->removeFromList();
    mate50->createMessage("Mate50即将售罄......");
    delete mate50;
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete c5;
}