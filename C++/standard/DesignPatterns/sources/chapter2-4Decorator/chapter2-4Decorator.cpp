#include <iostream>
#include <string>

//接口：具体被包裹的类，以及装饰类
class Beverage {
public:
    virtual ~Beverage(){}
    virtual std::string Operation() const = 0;
};
//具体的被装饰者
class Americano :public Beverage {
public:
    ~Americano() {}
    std::string Operation() const{
        return "美式咖啡";
    }
};
//装饰
//基础部分（可能包括额外部分）
class Ingredient :public Beverage {
protected:
    Beverage* m_beverage;
public:
    ~Ingredient() {}
    Ingredient(Beverage* beverage):m_beverage(beverage){}
    std::string Operation() const override {
        return m_beverage->Operation();//核心代码,不是用来被基类覆盖的
    }
};
//额外部分（需要委托基类，完成基础部分）
class Whip :public Ingredient {
public:
    ~Whip() {}
    Whip(Beverage* beverage) :Ingredient(beverage) {

    }
    std::string Operation() const override {
        //在基类的operation之前，之后都可以增加额外的操作
        return "奶昔("+Ingredient::Operation()+")";
    }
};
class Mocha :public Ingredient {
public:
    ~Mocha() {}
    Mocha(Beverage* beverage) :Ingredient(beverage) {

    }
    std::string Operation() const override {
        //在基类的operation之前，之后都可以增加额外的操作
        return "摩卡(" + Ingredient::Operation() + ")";
    }
};

void ClientCode(Beverage* beverage) {
    std::cout << "执行结果：" << beverage->Operation();
}
int main()
{
    std::cout << "来一杯普通美式咖啡：\n";
    Beverage* americano = new Americano();
    ClientCode(americano);
    std::cout << "\n\n";

    std::cout << "来一杯双份摩卡+奶昔的美式咖啡：\n";
    Beverage* whip1 = new Whip(americano);
    Beverage* mocha1 = new Mocha(whip1);
    Beverage* mocha2 = new Mocha(mocha1);
    ClientCode(mocha2);
    
    delete americano;
    delete whip1;
    delete mocha1;
    delete mocha2;
}
