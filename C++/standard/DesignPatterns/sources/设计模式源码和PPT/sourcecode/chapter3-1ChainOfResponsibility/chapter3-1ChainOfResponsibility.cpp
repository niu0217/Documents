#include <iostream>
#include <string>
#include <list>

//class Handler {
//public:
//    virtual Handler* setNext(Handler* handler) = 0;
//    virtual std::string handle(std::string request) = 0;
//};

class BaseHandler/*:public Handler*/{
private:
    BaseHandler* m_nextHandler;
public:
    BaseHandler* setNext(BaseHandler* handler) {
        m_nextHandler = handler;
        return m_nextHandler;
    }
    virtual std::string handle(std::string request) {
        if (m_nextHandler) {
            return m_nextHandler->handle(request);
        }

        return "";
    }
};

class RobotAI :public BaseHandler {
public:
    std::string handle(std::string request) override {
        if (request == "使用向导") {
            return "RobotAI:我来处理-" + request + "-。\n";
        }
        else {
            return BaseHandler::handle(request);
        }
    }
};
class TelOperator :public BaseHandler {
public:
    std::string handle(std::string request) override {
        if (request == "常见问题") {
            return "TelOperator:我来处理-" + request + "-。\n";
        }
        else {
            return BaseHandler::handle(request);
        }
    }
};
class Expert :public BaseHandler {
public:
    std::string handle(std::string request) override {
        if (request == "疑难杂症") {
            return "Expert:我来处理-" + request + "-。\n";
        }
        else {
            return BaseHandler::handle(request);
        }
    }
};

void clientCode(BaseHandler& handler) {
    std::list<std::string> problems = { "疑难杂症","常见问题","使用向导","常见问题","扯淡的问题" };
    for (const std::string& problem : problems) {
        std::string result = handler.handle(problem);
        std::cout << "Client：谁来处理" << problem<<":\n";
        if (result.empty()) {
            std::cout << "处理结果：" << "没人能够处理。\n";
        }
        else
        {
            std::cout << "处理结果：" << result;
        }
    }
}
int main()
{
    RobotAI robot;
    TelOperator telOperator;
    Expert expert;
    robot.setNext(&telOperator)->setNext(&expert);
    std::cout << "Chain：机器人AI->话务员->专家\n";
    clientCode(robot);

    //clientCode(telOperator);
}

