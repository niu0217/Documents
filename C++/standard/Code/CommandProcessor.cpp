#include<iostream>
#include<memory>
#include<stack>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class Revertable {
public:
    virtual ~Revertable() = default;
    virtual void undo() = 0;
};

class UndoableCommand : public Command, public Revertable { };

using CommandPtr = std::shared_ptr<Command>;

class DrawingProcessor;

class DrawCircleCommand : public UndoableCommand {
public:
    DrawCircleCommand(DrawingProcessor& receiver, const Point& centerPoint,
            const double radius) noexcept
        : receiver{ receiver }, centerPoint{ centerPoint }, radius{ radius} { }
    void execute() override {
        receiver.drawCircle(centerPoint, radius);
    }
    void undo() override {
        receiver.eraseCircle(centerPoint, radius);
    }
private:
    DrawingProcessor& receiver;
    const Point centerPoint;
    const double radius;
};

class DrawingProcessor {
public:
    void drawCircle(const Point& centerPoint, const double radius) {
        //
    }
    void eraseCircle(const Point& centerPoint, const double radius) {
        //
    }
};

class CommandProcessor {
public:
    void execute(const CommandPtr& command) {
        command->execute();
        commandHistory.push(command);
    }
    void undoLastCommand() {
        if(commandHistory.empty()) {
            return;
        }
        commandHistory.top()->undo();
        commandHistory.pop();
    }
private:
    std::stack<std::shared_ptr<Revertable>> commandHistory;
};

class UndoCommand : public UndoableCommand {
public:
    explicit UndoCommand(CommandProcessor& receiver) noexcept
        : receiver{ receiver }
    void execute() override {
        receiver.undoLastCommand();
    }
    void undo() override {
        //
    }
private:
    CommandProcessor& receiver;
};

