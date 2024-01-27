#include <iostream>

//Target:客户端需要的目标接口
class JasonInfo {
public:
    virtual ~JasonInfo(){}

    virtual std::string request() const {
        return "Some Jason information.......";
    }
};

//Adaptee:客户端不兼容的接口，需要转换为Target接口
class XmlInfo {
public:
    std::string specialRequest() const {
        return "Some Xml information.......";
    }
};

//Adaptor:适配器，就是把Adaptee包装起来，让他看上去像是Target
class XmlJasonAdapter :public JasonInfo {
private:
    XmlInfo* m_adaptee;
public:
    XmlJasonAdapter(XmlInfo* adaptee) :m_adaptee(adaptee) {}

    virtual std::string request() const override{
        std::string string=m_adaptee->specialRequest();
        return "Jason<-XmlJasonAdaptor<-"+ string;
    }
};

void clientCode(const JasonInfo* info) {
    
    std::cout << "股票分析软件运行Jason：" <<
        info->request()<<std::endl;
    std::cout << "----------------------------------------\n";
}
int main()
{
    JasonInfo jasonInfo;
    clientCode(&jasonInfo);
    XmlInfo xmlInfo;
    XmlJasonAdapter jasonAdpater(&xmlInfo);
    clientCode(&jasonAdpater);
}
