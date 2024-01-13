#include<iostream>
#include<memory>
#include<vector>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute() = 0;
};

class StrategyA : public Strategy {
public:
    void execute() override {
        std::cout<<"StrategyA\n";
    }
};

class StrategyB : public Strategy {
public:
    void execute() override {
        std::cout<<"StrategyB\n";
    }
};

using StrategyPtr = std::shared_ptr<Strategy>;

class Application {
public:
    explicit Application(StrategyPtr initialStrategy)
        : strategy{ initialStrategy } { }
    void run() {
        strategy->execute();
    }
    void setStrategy(StrategyPtr newStrategy) {
        strategy = newStrategy;
    }
private:
    StrategyPtr strategy;
};

int main()
{
    auto app = std::make_shared<Application>(std::make_shared<StrategyA>());
    app->run();

    app->setStrategy(std::make_shared<StrategyB>());
    app->run();
}

