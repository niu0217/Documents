#include<iostream>
#include<string>
#include<string_view>
#include<memory>

class LoggerFactory {
private:
    enum class OutputTarget : int {
        STDOUT,
        FILE
    };
public:
    explicit LoggerFactory(std::string_view configurationFileName)
        : configurationFileName{ configurationFileName } { }
    Logger create() const {
        const std::string configurationFileContent = readConfigurationFile();
        OutputTarget outputTarget = evaluateConfiguration(configurationFileContent);
        return createLogger(outputTarget);
    }
private:
    std::string readConfigurationFile() const {
        std::ifstream filestream(configurationFileName);
        return std::string(std::istreambuf_iterator<char>(filestream),
                std::istreambuf_iterator<char>());
    }
    OutputTarget evaluateConfiguration(std::string_view configurationFileContent) const {
        return OutputTarget::STDOUT;
    }
    Logger createLogger(OutputTarget outputTarget) const {
        switch(outputTarget) {
            case OutputTarget::FILE:
                return std::make_shared<FilesystemLogger>();
            case OutputTarget::STDOUT:
            default:
                return std::make_shared<StandardOutputLogger>();
        }
    }
    const std::string configurationFileName;
};

