#include <GL/glut.h>

#include "Window.hpp"
#include "GlutInit.hpp"

int main(int argc, char **argv)
{
    std::unique_ptr<Window> _window = std::make_unique<Window>(600, 800, argc, argv);

    _window->initGameLogic();
    _window->launchGameLogic();
    return 0;
}
