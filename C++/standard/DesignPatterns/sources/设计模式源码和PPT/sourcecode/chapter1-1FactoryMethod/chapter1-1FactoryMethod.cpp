#include <iostream>
//产品的接口
class Transport {
public:
    virtual ~Transport(){}
    virtual void deliver() const = 0;
};
//产品A
class Truck:public Transport {
public:
    void deliver() const override{
        std::cout << "卡车运输货物中ing。\n";
    }
};
//产品B
class Ship :public Transport {
public:
    void deliver() const override {
        std::cout << "轮船运输货物中ing。\n";
    }
};
//创造者（注意：除了创建产品以外，创造者还有自己的业务需要处理）
class Logistics {
public:
    virtual ~Logistics(){}
    //工厂方法的核心
    virtual Transport * factoryMethod() const = 0;
    void doSomething() const {
        Transport * transport= factoryMethod();
        transport->deliver();
        delete transport;
    }
};
//具体的创造者A
class TruckLogistis:public Logistics {
public:
    virtual ~TruckLogistis(){}
    virtual Transport* factoryMethod() const override{
        return new Truck();
    }
};
//具体的创造者B
class ShipLogistis :public Logistics {
public:
    virtual ~ShipLogistis() {}
    virtual Transport* factoryMethod() const override {
        return new Ship();
    }
};
int main()
{
    Logistics* truckLogistics = new TruckLogistis();
    Logistics* shipLogistics = new ShipLogistis();

    truckLogistics->doSomething();
    truckLogistics->doSomething();
   
    shipLogistics->doSomething();
    shipLogistics->doSomething();
    shipLogistics->doSomething();
    delete truckLogistics;
    delete shipLogistics;
}
