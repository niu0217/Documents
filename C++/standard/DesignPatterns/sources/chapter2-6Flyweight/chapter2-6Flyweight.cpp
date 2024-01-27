#include <iostream>
#include <string>
#include <unordered_map>

using std::string;
//内部状态
struct SharedState {
    string m_brand;
    string m_model;
    string m_color;

    SharedState(const string& brand,const string model,const string color):
        m_brand(brand),m_model(model),m_color(color){}

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss) {
        return os << "[" << ss.m_brand << "," << ss.m_model << "," << ss.m_color << "]";
    }
};
//外部状态
struct UniqueState
{
    std::string m_owner;
    std::string m_plates;

    UniqueState(const std::string& owner, const std::string& plates)
        : m_owner(owner), m_plates(plates)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us)
    {
        return os << "[ " << us.m_owner << " , " << us.m_plates << " ]";
    }
};

//享元，存放共享状态，内部状态
class Flyweight {
private:
    SharedState m_sharedState;
public:
    Flyweight(const SharedState sharedState):m_sharedState(sharedState){}
    void operation(UniqueState uniqueState) const//使用的时候，使用外部状态作为参数，对整个context做出操作
    {
        std::cout << "Flyweight:显示内部状态（"
            << m_sharedState << "),显示外部状态：（"
            << uniqueState << ")\n";
    }
};

class FlyweightFactory {
private:
    std::unordered_map<string, Flyweight> m_Flyweights;

    string getKey(const SharedState& ss) const
    {
        return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
    }
public:
    FlyweightFactory(std::initializer_list<SharedState> share_states)
    {
        for (const SharedState& ss : share_states) {
            m_Flyweights.insert({ getKey(ss),Flyweight(ss) });
        }
    }

    Flyweight* getFlyWeight(const SharedState& shared_state) {
        string key = getKey(shared_state);
        if (m_Flyweights.find(key) == m_Flyweights.end()) {
            std::cout << "FlyweightFactory:没有找到需要的享元，创建一个新的。\n";
            m_Flyweights.insert({ key,shared_state });
        }
        else {
            std::cout << "FlyweightFactory:返回一个现有的享元。\n";
        }
        return &m_Flyweights.at(key);
    }

    void listFlyWeights() const
    {
        int count = m_Flyweights.size();
        std::cout << "\nFlyweightFactory:我有" << count << "个享元：\n";
        for (std::pair<std::string, Flyweight> item : m_Flyweights) {
            std::cout << item.first << "\n";
        }
    }
};

class CarInfoContext {
private:
    Flyweight* m_flyWeight = nullptr;//内部状态
    UniqueState m_uniqueState;//外部状态
public:
    CarInfoContext(Flyweight* flyWeight,const UniqueState * unique_state):
        m_flyWeight(flyWeight),m_uniqueState(*unique_state){}
    void operation() {
        m_flyWeight->operation(m_uniqueState);
    }
};
//Client
class PoliceCarDatabase {
private:
    std::list<CarInfoContext*> carInfoDatabase;
public:
    ~PoliceCarDatabase() {
        for (auto item : carInfoDatabase)
            delete item;
    }

    void addCarToPoliceDatabase(FlyweightFactory &ff,
        const string& owner,const string& plates,
        const string& brand,const string& model,const string& color){
        std::cout << "\n客户端：添加车辆信息到数据库。\n";
        Flyweight* flyWeight = ff.getFlyWeight({ brand,model,color });//内部状态
        UniqueState uniqueState(owner, plates);//外部状态
        carInfoDatabase.push_back(new CarInfoContext(flyWeight, &uniqueState));
        std::cout << "\n客户端：数据库当前状态：\n";
        for (auto item : carInfoDatabase)
        {
            item->operation();
        }
    }
};
int main()
{
    FlyweightFactory factory({
        SharedState("奔驰","GLC","白色"),
        SharedState("奥迪","A7","黑色"),
        SharedState("宝马","X1","白色")
        });
    factory.listFlyWeights();

    PoliceCarDatabase database;
    database.addCarToPoliceDatabase(factory,
        "阿西拜", "赣ABC888", "奔驰", "GLC", "白色");
    factory.listFlyWeights();
    database.addCarToPoliceDatabase(factory,
        "阿西拜", "赣ABC999", "比亚迪", "唐EV", "蓝色");
    database.addCarToPoliceDatabase(factory,
        "阿西拜", "赣ABC666", "奔驰", "GLC", "白色");
    factory.listFlyWeights();
}