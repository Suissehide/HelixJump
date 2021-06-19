#ifndef Window_hpp
#define Window_hpp

#include <memory>

class Window
{
private:
    int _height;
    int _width;

    void _initWindow(int argc, char **argv);
    void _initLight();
public:
    Window(int height, int width, int argc, char **argv);
    ~Window() = default;

    void initGameLogic();
    void launchGameLogic();
};


#endif // !Window_hpp