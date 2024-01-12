#include<iostream>
#include<chrono>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<string>
#include<ctime>

class Logger {
public:
    Logger() = default;
    virtual ~Logger() = default;
    void showInfoLog(const std::string& infoLogMessage);
    void showWarningLog(const std::string& warningLogMessage);
    void showErrorLog(const std::string& errorLogMessage);
    std::string getCurrentTime();
private:
    void recordLog(const std::string& logLevel, const std::string& logMessage);
};

void Logger::showInfoLog(const std::string& infoLogMessage) {
    recordLog("INFO", infoLogMessage);
}

void Logger::showWarningLog(const std::string& warningLogMessage) {
    recordLog("WARNING", warningLogMessage);
}

void Logger::showErrorLog(const std::string& errorLogMessage) {
    recordLog("ERROR", errorLogMessage);
}

std::string Logger::getCurrentTime() {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t timeOfTypeTimet = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* timeOfTypeLocalTime = std::localtime(&timeOfTypeTimet);
    std::ostringstream outputStream;
    outputStream<<std::put_time(timeOfTypeLocalTime, "%Y-%m-%d %H:%M:%S");
    return outputStream.str();
}

void Logger::recordLog(const std::string& logLevel, const std::string& logMessage) {
    std::string currentTime = getCurrentTime();
    std::cout<<"["<<currentTime<<"]["<<logLevel<<"]"<<logMessage<<std::endl;
}

int main()
{
    Logger logger;
    logger.showInfoLog("This is a info message");
    logger.showErrorLog("This is a error message");
    logger.showWarningLog("This is a warning message");
    return 0;
}

