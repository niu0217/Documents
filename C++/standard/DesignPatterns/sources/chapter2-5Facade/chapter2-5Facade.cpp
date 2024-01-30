#include <iostream>
#include <string>

//子系统1
class VideoSystem {
public:
    std::string initial() const {
        return "视频系统：Ready!\n";
    }
    std::string play() const {
        return "视频系统：Go!\n";
    }
    //.....
    std::string operationX() const {
        return "视频系统：不常用的骚操作!\n";
    }
};
//子系统2
class RadioSystem {
public:
    std::string init() const {
        return "音频系统：就绪!\n";
    }
    std::string play() const {
        return "音频系统：播放!\n";
    }
    //.....
    std::string operationX() const {
        return "音频系统：不常用的骚操作!\n";
    }
    std::string mute() const {
        return "音频系统：静音!\n";
    }
};
//外观
class Controller {
protected:
    VideoSystem* m_video;
    RadioSystem* m_radio;
public:
    Controller(VideoSystem* video = nullptr, RadioSystem* radio = nullptr)
        : m_video{ video ? video : new VideoSystem },
          m_radio{ radio ? radio : new RadioSystem } { }
    ~Controller() {
        delete m_video;
        delete m_radio;
    }
    std::string start() {
        std::string string = "控制器启动系统：\n";
        string += m_video->initial();
        string += m_radio->init();
        string += "控制器播放;\n";
        string += m_video->play();
        string += m_radio->play();
        return string;
    }
    std::string mute() {
        return m_radio->mute();
    }
};
int main()
{
    VideoSystem* video = new VideoSystem;
    RadioSystem* radio = new RadioSystem;
    Controller controller(video, radio);//外观对象，负责回收子系统
    std::cout << controller.start();
}