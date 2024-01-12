#include<iostream>
#include<memory>
#include<string>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual int execute(int valueA, int valueB) = 0;
};

using StrategyPtr = std::shared_ptr<Strategy>;

class AdditionStrategy : public Strategy {
public:
    int execute(int valueA, int valueB) override {
        return valueA + valueB;
    }
};

class SubtractionStrategy : public Strategy {
public:
    int execute(int valueA, int valueB) override {
        return valueA - valueB;
    }
};

class MultiplicationStrategy : public Strategy {
public:
    int execute(int valueA, int valueB) override {
        return valueA * valueB;
    }
};

class DivisionStrategy : public Strategy {
public:
    int execute(int valueA, int valueB) override {
        if(valueB != 0) {
            return valueA / valueB;
        }
        else {
            std::cerr<<"Division by zero is not allowed!"<<std::endl;
            return 0;
        }
    }
};

class Context {
public:
    Context(StrategyPtr strategy) : strategy(strategy) { }
    ~Context() = default;
    int executeStrategy(int valueA, int valueB) {
        return strategy->execute(valueA, valueB);
    }
private:
    StrategyPtr strategy;
};

int main()
{
    StrategyPtr addition = std::make_shared<AdditionStrategy>();
    StrategyPtr subtraction = std::make_shared<SubtractionStrategy>();
    StrategyPtr multiplication = std::make_shared<MultiplicationStrategy>();
    StrategyPtr division = std::make_shared<DivisionStrategy>();

    Context context(addition);
    std::cout << "Addition: " << context.executeStrategy(5, 3) << std::endl;

    context = Context(subtraction);
    std::cout << "Subtraction: " << context.executeStrategy(5, 3) << std::endl;

    context = Context(multiplication);
    std::cout << "Multiplication: " << context.executeStrategy(5, 3) << std::endl;

    context = Context(division);
    std::cout << "Division: " << context.executeStrategy(5, 3) << std::endl;
}

