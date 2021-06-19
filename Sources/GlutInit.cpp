#include <GL/glut.h>
#include <math.h>
#include <ctype.h>
#include <vector>

#include "GlutInit.hpp"
#include "GameLogic.hpp"

static int width = 800;
static int height = 600;

namespace utils
{
    float angle = 0;
    float ANGLE = 360 / 120;
    float moveScreenX = 0;
    bool Falling = true;
    bool pause = true;
    float translateSphere = INITIAL_POINT, accelerateSphere = 0.15;
    float descent = DISTANCE_INTERPLATFORM * NBR_LEVEL;
}
static bool fullScreen = true;
static int distOrigin = 100;
static float horizontalTranslate = 0, topSide = 0;
static float current = 0;
static bool releaseMouse = false;
static float accelerateSphere = 0.15;
static int last_x, last_y;


void reshape(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-1, 1, -1 * (GLfloat)height / (GLfloat)width, 1 * (GLfloat)height / (GLfloat)width, -10.0, 10.0);
    else
        glOrtho(-1 * (GLfloat)width / (GLfloat)height, 1 * (GLfloat)width / (GLfloat)height, -1, 1, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int, int)
{
    switch (tolower(key))
    {
    case '+':
        distOrigin--;
        break;
    case '-':
        distOrigin++;
        break;

    case 'w':
        topSide += 10;

        break;
    case 'a':
        horizontalTranslate -= 3;

        break;
    case 's':
        if (topSide >= 10)
            topSide -= 10;

        break;
    case 'd':
        horizontalTranslate += 3;

        break;
    case 'f':
        fullScreen = !fullScreen;
        if (fullScreen)
        {
            glutFullScreen();
        }
        else
        {
            glutReshapeWindow(width, height);
        }
        break;
    case 'r':
        gameLogicInstance.lostGame();
        break;
    case 'p':
        utils::pause = !utils::pause;
        break;

    case 27:
        exit(0);
        break;
    }
}

void motion(int x, int)
{
    static bool just_warped = false;

    if (just_warped)
    {
        just_warped = false;
        return;
    }

    float dx = x - width / 2;

    if (dx > 0)
        utils::moveScreenX += -1 * (abs(dx));
    if (dx < 0)
        utils::moveScreenX += +1 * (abs(dx));
    if (utils::moveScreenX > 360)
        utils::moveScreenX = 0 + utils::moveScreenX - 359;
    if (utils::moveScreenX < 0)
        utils::moveScreenX = 359 + utils::moveScreenX;
    utils::moveScreenX = utils::moveScreenX;

    if (!releaseMouse)
        glutWarpPointer(width / 2, height / 2);

    just_warped = true;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        last_x = x;
        last_y = y;
    }
    if (button == 0)
    {
        gameLogicInstance.restartGame();
    }

    if (button == 3)
    {
        distOrigin--;
        if (distOrigin < 20)
            distOrigin = 20;
    }
    if (button == 4)
    {
        distOrigin++;
        if (distOrigin > 180)
            distOrigin = 180;
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat light[] = {0, 0, 100, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, light);

    gluLookAt(0, utils::descent + 50, 120, 0.0, 0.0 + utils::descent + 50 - 58, 0, 0.0, 58, 0);

    std::vector<int> mainAxis{360, 4};

    gameLogicInstance.drawsGame();
    glPushMatrix();
    glRotatef(utils::moveScreenX - 90, 0.0, 1.0, 0.0);
    gameLogicInstance.drawingLevel(25, 0, DISTANCE_INTERPLATFORM * (NBR_LEVEL), mainAxis);

    gameLogicInstance.scenarioDesign();
    glPopMatrix();

    glutSwapBuffers();
}

void idle()
{
    if (current <= 360)
    {
        utils::angle += utils::ANGLE;
        current++;
    }
    if (utils::pause)
        return;
    utils::translateSphere += accelerateSphere;
    glutPostRedisplay();
}