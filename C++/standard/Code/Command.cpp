#include<iostream>
#include<memory>
#include<chrono>
#include<thread>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

using CommandPtr = std::shared_ptr<Command>;

class HelloWorldOutputCommand : public Command {
public:
    void execute() override {
        std::cout<<"Hello World!\n";
    }
};

class WaitCommand : public Command {
public:
    explicit WaitCommand(const unsigned int durationInMilliseconds) noexcept
        : durationInMilliseconds{ durationInMilliseconds } { }
    void execute() override {
        std::chrono::milliseconds dur(durationInMilliseconds);
        std::this_thread::sleep_for(dur);
    }
private:
    unsigned int durationInMilliseconds{ 1000 };
};

class Server {
public:
    void acceptCommand(const CommandPtr& command) {
        command->execute();
    }
};

class Client {
public:
    void run() {
        Server theServer{};
        const unsigned int SERVER_DELAY_TIMESPAN{ 3000 };

        CommandPtr waitCommand = std::make_shared<WaitCommand>(SERVER_DELAY_TIMESPAN);
        theServer.acceptCommand(waitCommand);

        CommandPtr helloWorldOutputCommand = std::make_shared<HelloWorldOutputCommand>();
        theServer.acceptCommand(helloWorldOutputCommand);
    }
};

int main()
{
    Client client{};
    client.run();
    return 0;
}

