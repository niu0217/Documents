#include <iostream>

//接口：真实的数据库和代理数据都依赖这个接口
class Database {
public:
    virtual void request() const = 0;
};
//
class RealDatabase:public Database {
public:
    void request() const override {
        std::cout << "--真实数据库：处理业务请求。\n";
    }
};
//
class ProxyDatabase :public Database {
private:
    RealDatabase* m_realDatabase;
    bool checkAccess() const {
        std::cout << "ProxyDatabase：在发出请求之前，检查一下。\n";
        return true;
    }
    void log() const {
        std::cout<<"ProxyDatabase：处理日志。\n";
    }
public:
    ProxyDatabase(RealDatabase* realDatabase):m_realDatabase(realDatabase){}

    void request() const override {
        if(checkAccess()){
            std::cout << "ProxyDatabase：通过代理处理数据库请求。\n";
            m_realDatabase->request();
            log();
        }
        else {
            std::cout << "ProxyDatabase：数据库访问请求被驳回。\n";
        }      
    }
};

void clientCode(const Database& database) {
    database.request();
}
int main()
{
    std::cout << "Client:直接使用真实数据库处理请求：\n";
    RealDatabase realDatabase;
    clientCode(realDatabase);
    std::cout << "Client:通过代理处理数据库请求：\n";
    ProxyDatabase proxy(&realDatabase);
    clientCode(proxy);
}
