#include<iostream>
#include<string_view>

class Logger final {
public:
    static Logger& getInstance() {
        static Logger theLogger{ };
        return theLogger;
    }
    void writeInfoEntry(std::string_view) {
        //
    }
    void writeWarnEntry(std::string_view) {
        //
    }
    void writeErrorEntry(std::string_view) {
        //
    }
};

class LoggingFacility {
public:
    virtual ~LoggingFacility() = default;
    virtual void writeInfoEntry(std::string_view entry) = 0;
    virtual void writeWarnEntry(std::string_view entry) = 0;
    virtual void writeErrorEntry(std::string_view entry) = 0;
};

class StandardOutputLogger : public LoggingFacility {
public:
    void writeInfoEntry(std::string_view entry) override {
        std::cout<<"[INFO]"<<entry<<std::endl;
    }
    void writeWarnEntry(std::string_view entry) override {
        std::cout<<"[WARNING]"<<entry<<std::endl;
    }
    void writeErrorEntry(std::string_view entry) override {
        std::cout<<"[ERROR]"<<entry<<std::endl;
    }
};

class CustomerRespository {
public:
    CustomerRespository() = delete;
    explicit CustomerRespository(const Logger& loggingService)
        : logger{ loggingService } { }
    Customer findCustomerById(const Identifier& customerId) {
        logger->writeInfoEntry("....");
    }
private:
    Logger logger;
};

