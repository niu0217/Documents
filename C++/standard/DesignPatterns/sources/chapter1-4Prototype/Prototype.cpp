#include <iostream>
#include <unordered_map>
using std::string;

enum Type {
    ROBOT_CAT = 0,
    ROBOT_DOG
};

class Robot {
protected:
    string m_prototype_name="";
    float m_stateOfCharge=0;
public:
    Robot() = default;
    Robot(string name):m_prototype_name(name) {

    }
    virtual ~Robot(){}
    virtual Robot* clone() const = 0;
    virtual void setStateOfCharge(float) = 0;
};

class RobotCat:public Robot {
private:
    float m_CatValue = 0;
public:
    virtual ~RobotCat(){}
    RobotCat(const RobotCat& robot) {
        m_CatValue = robot.m_CatValue;
    }
    RobotCat(string name, float value) :Robot(name), m_CatValue(value) {

    } 
    virtual Robot* clone() const override{
        return new RobotCat(*this);
    }

    virtual void setStateOfCharge(float value) override{
        m_stateOfCharge = value;
        //下面这种逻辑不好，需要分离
        std::cout << "--" << m_prototype_name << " 当前电量：" << m_stateOfCharge
            << ",m_CatValue:" << m_CatValue << std::endl;
    }
};
class RobotDog:public Robot {
private:
    float m_DogValue = 0;
public:
    virtual ~RobotDog() {}
    RobotDog(string name, float value) :Robot(name), m_DogValue(value) {

    }
    virtual Robot* clone() const override {
        return new RobotDog(*this);
    }

    virtual void setStateOfCharge(float value) override {
        m_stateOfCharge = value;
        //下面这种逻辑不好，需要分离
        std::cout << "--" << m_prototype_name << " 当前电量：" << m_stateOfCharge
            << ",m_DogValue:" << m_DogValue << std::endl;
    }
};
class CloneFactory {
    std::unordered_map<Type, Robot*> m_prototypes;
public:
    CloneFactory() {
        m_prototypes[ROBOT_CAT] = new RobotCat("机器猫", 5.0);
        m_prototypes[ROBOT_DOG] = new RobotDog("机器狗", 8.0);
    }
    ~CloneFactory() {
        delete m_prototypes[ROBOT_CAT];
        delete m_prototypes[ROBOT_DOG];
    }
    Robot* createRobot(Type type) {
        return m_prototypes[type]->clone();
    }
};

void clintcode(CloneFactory& cloneFactory) {
    std::cout << "克隆机器猫：\n";
    Robot* cloneRobot = cloneFactory.createRobot(ROBOT_CAT);
    cloneRobot->setStateOfCharge(90);
    delete cloneRobot;
    cloneRobot = cloneFactory.createRobot(ROBOT_CAT);
    cloneRobot->setStateOfCharge(80);
    delete cloneRobot;
    std::cout << "克隆机器狗：\n";
    cloneRobot = cloneFactory.createRobot(ROBOT_DOG);
    cloneRobot->setStateOfCharge(75);
    delete cloneRobot;
}
int main()
{
    CloneFactory cloneFactory;
    clintcode(cloneFactory);
}

