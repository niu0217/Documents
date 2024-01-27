#include <iostream>
#include <string>
class Staff;
//Mediator Interface
class ControlTower {
public:
    virtual void notify(Staff* sender, std::string event) const = 0;
};

class Staff {
protected:
    std::string m_name;
    ControlTower* m_controlTower;
public:
    Staff(std::string name, ControlTower* controlTower = nullptr) 
    :m_name(name),m_controlTower(controlTower){

    }
    std::string name() { return m_name; }
    void setMediator(ControlTower* controlTower) {
        m_controlTower = controlTower;
    }
};
class Pilot :public Staff {
public:
    Pilot(std::string name):Staff(name){}

    void takeOff() {
        std::cout << name() + ":请求起飞。\n";
        m_controlTower->notify(this, "起飞请求");
    }
    void copy() {
        std::cout << name() + ":收到。\n";
        //m_controlTower->notify(this, "收到");
    }
};

class GroundGrew :public Staff {
public:
    GroundGrew(std::string name) :Staff(name) {}

    void maintainance() {
        std::cout << name() + ":请求维护。\n";
        m_controlTower->notify(this, "请求维护");
    }
    void copy() {
        std::cout << name() + ":收到。\n";
        //m_controlTower->notify(this, "收到");
    }
};
class ConcreteControlTower :public ControlTower {
private:
    Pilot* m_pilot1;
    Pilot* m_pilot2;
    Pilot* m_pilot3;
    GroundGrew* m_ground1;
public:
    ConcreteControlTower(Pilot* p1, Pilot* p2, Pilot* p3, GroundGrew* g1)
    :m_pilot1(p1), m_pilot2(p2), m_pilot3(p3),m_ground1(g1) {
        m_pilot1->setMediator(this);
        m_pilot2->setMediator(this);
        m_pilot3->setMediator(this);
        m_ground1->setMediator(this);
    }

    void notify(Staff* sender, std::string event) const override {
        std::cout << "控制塔：收到" + sender->name() + event + "。\n";
        if (event == "起飞请求") {
            
            m_ground1->copy();
            if(sender!= m_pilot1)
                m_pilot1->copy();
            if (sender != m_pilot2)
                m_pilot2->copy();
            if (sender != m_pilot3)
                m_pilot3->copy();
        }

        if (event == "请求维护") {
            
                m_pilot1->copy();
                m_pilot2->copy();
                m_pilot3->copy();
        }
    }
};
int main()
{
    Pilot* p1 = new Pilot("空军1号");
    Pilot* p2 = new Pilot("空军2号");
    Pilot* p3 = new Pilot("空军3号");
    GroundGrew* g1 = new GroundGrew("地勤1");
    ConcreteControlTower* controlTower = new ConcreteControlTower(p1, p2, p3, g1);
    p1->takeOff();
    g1->maintainance();
    delete p1;
    delete p2;
    delete p3;
    delete g1;
}
