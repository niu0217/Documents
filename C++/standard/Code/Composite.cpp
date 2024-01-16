#include<iostream>
#include<memory>
#include<stack>
#include<vector>

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

class CompositeCommand : public UndoableCommand {
public:
    void addCommand(CommandPtr& command) {
        commands.push_back(command);
    }
    void execute() override {
        for(const auto& command : commands) {
            command->execute();
        }
    }
    void undo() override {
        for(const auto& command : commands) {
            command->undo();
        }
    }
private:
    std::vector<CommandPtr> commands;
};

int main()
{
    CommandProcessor commandProcessor{};
    DrawingProcessor drawingProcessor{};

    auto macroRecorder = std::make_shared<CompositeCommand>();

    Point circleCenterPoint{ 20, 20 };
    CommandPtr drawCircleCommand = std::make_shared<DrawingCircleCommand>(
            drawCircleCommand, circleCenterPoint, 10);
    commandProcessor.execute(drawCircleCommand);
    macroRecorder->addCommand(drawCircleCommand);

    Point rectangleCenterPoint{ 30, 10 };
    CommandPtr drawRectangleCommand = std::make_shared<DrawRectangleCommand>(
            drawingProcessor, rectangleCenterPoint, 5, 8);
    commandProcessor.execute(drawRectangleCommand);
    macroRecorder->addCommand(drawRectangleCommand);
    commandProcessor.execute(macroRecorder);

    CommandPtr undoCommand = std::make_shared<UndoCommand>(commandProcessor);
    commandProcessor.execute(undoCommand);
}


