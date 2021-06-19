#include <GL/glut.h>
#include <functional>

#include "Window.hpp"
#include "GlutInit.hpp"
#include "GameLogic.hpp"

Window::Window(int height, int width, int argc, char **argv)
:_height(height), _width(width)
{
    _initWindow(argc, argv);
    _initLight();
}

void Window::_initWindow(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(_width, _height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutSetCursor(GLUT_CURSOR_NONE);

    glutIgnoreKeyRepeat(1);
}

void Window::_initLight() {
    glClearColor(0.1, 0.1, 0.1, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    GLfloat colour_light[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position[] = {0, 0, 100, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, colour_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, colour_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, colour_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void Window::initGameLogic() {
    gameLogicInstance.createScenarii();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);

    glutKeyboardFunc(keyboard);
    glutFullScreen();

    glutIdleFunc(idle);
}

void Window::launchGameLogic() {
    glutMainLoop();
}