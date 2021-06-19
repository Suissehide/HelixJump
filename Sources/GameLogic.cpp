#include <math.h>
#include <ctype.h>
#include <memory>

#include "GameLogic.hpp"
#include "Materials.hpp"

using namespace std;

static float transposition = (NBR_LEVEL - 1) * (DISTANCE_INTERPLATFORM);

static float pos;

static int redSpeed[NBR_LEVEL] = {1, 3, 1, -2, -1, -3, 2, -1, 2, -1, -1, -2, 1, 1, 3, -1, 3, 2, 1, -1, 1, 3, 1, -2, -1, -3, 2, -1, 2, -1, -1, -2, 1, 1, 3, -1, 3, 2, 1, 0};
static vector<int> patterns[] = {
    vector<int>{0, 0, 40, 1, 40, 2, 40, 1, 40, 0, 40, 1, 40, 2, 40, 1},
    vector<int>{0, 0, 40, 2, 40, 1, 40, 2, 40, 0, 40, 2, 40, 1, 40, 2},
    vector<int>{0, 0, 290, 2},
    vector<int>{0, 0, 50, 2, 50, 1, 70, 2, 20, 0, 50, 1, 70, 2},
    vector<int>{0, 0, 50, 2, 50, 1, 70, 2, 50, 1, 20, 0, 70, 2},
    vector<int>{0, 0, 70, 2, 50, 1, 70, 2, 50, 0, 70, 2},
    vector<int>{0, 0, 70, 2, 50, 0, 70, 2, 50, 0, 70, 2},

    vector<int>{0, 0, 130, 2, 50, 0, 130, 2},
    vector<int>{0, 0, 40, 2, 40, 0, 30, 1, 30, 0, 40, 2, 40, 0, 30, 1, 30, 0, 20, 2},
    vector<int>{0, 0, 95, 2, 40, 0, 30, 1, 50, 0, 95, 2},

};

static vector<int> destroys{
    30,
    2,
    30,
    7,
    30,
    2,
    30,
    7,
    30,
    2,
    30,
    7,
    30,
    2,
    30,
    7,
    30,
    2,
    30,
    7,
    30,
    2,
    30,
    7,
};


vertice_t *GameLogic::CalculatesNormal(float x1, float y1, float z1, float x2, float y2, float z2)
{
    vertice_t *vn = new vertice_t;
    double len;

    vn->x = (y1 * z2) - (z1 * y2);
    vn->y = (z1 * x2) - (x1 * z2);
    vn->z = (x1 * y2) - (y1 * x2);

    len = sqrt(pow(vn->x, 2) + pow(vn->y, 2) + pow(vn->z, 2));

    vn->x /= len;
    vn->y /= len;
    vn->z /= len;

    return vn;
}

GameLogic gameLogicInstance;

void GameLogic::drawMiddleSide(float start, float height, float g, bool frente, float ray)
{
    glPushMatrix();
    vertice_t *vn = CalculatesNormal(ray * cos(g * PI / 180), start, ray * sin(g * PI / 180), ray * cos(g * PI / 180), height, ray * sin(g * PI / 180));
    if (!frente)
    {
        vn->x = -vn->x;
        vn->y = -vn->y;
        vn->z = -vn->z;
    }
    glNormal3f(vn->x, vn->y, vn->z);
    glBegin(GL_QUADS);
    glVertex3f(ray * cos(g * PI / 180), start, ray * sin(g * PI / 180));
    glVertex3f(ray * cos(g * PI / 180), height, ray * sin(g * PI / 180));
    glVertex3f(0, height, 0);
    glVertex3f(0, start, 0);
    glEnd();
    glPopMatrix();
}

void GameLogic::drawLateral(float ray, float start, float height, vector<int> &vetor)
{
    bool right = false;
    float g = 0;
    float travelled = 0;

    for (std::size_t k = 0; k < vetor.size(); k += 2)
    {
        utils::angle = vetor[k];
        if (vetor[(k + 1)] != 0)
        {
            Materials::setMaterial(vetor[(k + 1)]);
            glPushMatrix();
            glBegin(GL_QUAD_STRIP);
            for (g = travelled; g <= travelled + utils::angle; g += 1)
            {
                glVertex3f(ray * cos(g * PI / 180), start, ray * sin(g * PI / 180));
                glVertex3f(ray * cos(g * PI / 180), height, ray * sin(g * PI / 180));
                glNormal3f(cos(g * PI / 180), 0, sin(g * PI / 180));
            }
            if (utils::angle == 360)
            {
                for (g = 360; g <= 362; g += 0.01)
                {
                    glVertex3f(ray * cos(g * PI / 180), start, ray * sin(g * PI / 180));
                    glVertex3f(ray * cos(g * PI / 180), height, ray * sin(g * PI / 180));
                    glNormal3f(cos(g * PI / 180), 0, sin(g * PI / 180));
                }
            }
            glEnd();
            glPopMatrix();
            drawMiddleSide(start, height, travelled, right, ray);
            right = !right;
        }
        else
        {
            if (travelled != 0)
            {
                drawMiddleSide(start, height, travelled, right, ray);
                right = !right;
            }
        }
        travelled += utils::angle;
    }
    drawMiddleSide(start, height, travelled, right, ray);
    travelled = 0;
}

void GameLogic::drawingCap(float ray, float height, bool Cover, vector<int> &vetor)
{
    int g = 0;
    int travelled = 0;

    for (std::size_t k = 0; k < vetor.size(); k += 2)
    {
        utils::angle = vetor[k];
        if (vetor[(k + 1)] != 0)
        {
            Materials::setMaterial(vetor[(k + 1)]);
            glNormal3f(0, Cover ? 1 : -1, 0);

            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, height, 0);
            for (g = travelled; g <= travelled + utils::angle; g += 1)
            {
                glVertex3f(ray * cos(g * PI / 180), height, ray * sin(g * PI / 180));
                glNormal3f(0, Cover ? 1 : -1, 0);
            }
            glEnd();
        }
        travelled += utils::angle;
    }
    travelled = 0;
}

void GameLogic::drawingLevel(float ray, float start, float height, vector<int> &vetor)
{
    glPushMatrix();
    drawLateral(ray, start, height, vetor);
    drawingCap(ray, start, false, vetor);
    drawingCap(ray, height, true, vetor);
    glPopMatrix();
}

void GameLogic::lostGame()
{
    utils::pause = true;
}

bool GameLogic::_planeUnderBallSameLevel(vector<int *> &xPlan)
{
    if (!xPlan.empty())
    {
        for (std::size_t i = 0; i < xPlan.size(); i++)
        {
            if (utils::moveScreenX >= xPlan[i][0] && utils::moveScreenX <= xPlan[i][1])
            {
                return true;
            }
        }
    }
    return false;
}

bool GameLogic::_touchedPlaneUpOnSameLevel(float positionBallX, float positionBallY, vector<int *> &limBlackFlat)
{
    double dx = -4 * (positionBallX - 10);
    double threshold = 1.2 + 2.5;
    bool comp = positionBallY - 5 < (level)*DISTANCE_INTERPLATFORM + threshold && positionBallY - 5 > (level)*DISTANCE_INTERPLATFORM - threshold;

    return (comp && dx < 0 && _planeUnderBallSameLevel(limBlackFlat));
}

float GameLogic::_freefall(float x)
{
    pos = -2 * pow((x - 10), 2) + 50 + transposition;

    if (((pos + 5 + 1 < (level)*DISTANCE_INTERPLATFORM)) && !_touchedPlaneUpOnSameLevel(x, pos - 5, limBlackFlat[level]))
    {
        level--;
    }
    if (((pos - 5 < (level)*DISTANCE_INTERPLATFORM)) && !_touchedPlaneUpOnSameLevel(x, pos - 5, limBlackFlat[level]))
        utils::Falling = true;

    if (utils::Falling)
        utils::descent = pos;

    if (_touchedPlaneUpOnSameLevel(utils::moveScreenX, pos - 5, limRedFlat[level]))
    {
        lostGame();
    }
    if (_touchedPlaneUpOnSameLevel(x, pos - 5, limBlackFlat[level]))
    {
        transposition = (level)*DISTANCE_INTERPLATFORM;

        utils::translateSphere = INITIAL_POINT;
        if (utils::Falling)
        {
            utils::Falling = false;
        }
    }

    if (pos < 0)
    {
        lostGame();
    }

    return pos;
}

void GameLogic::drawsGame()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glutIdleFunc(idle);
    glTranslatef(0, -40, _freefall(utils::translateSphere));
    Materials::setMaterial(7);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();
}

void GameLogic::_vectorRestructuring()
{
    int pos = 0;

    limRedFlat[level].clear();
    limBlackFlat[level].clear();
    for (std::size_t i = 0; i < scenario[level].size(); i += 2)
    {
        if (scenario[level][i + 1] == 0)
        {
            pos += scenario[level][i];
        }
        else
        {
            if (scenario[level][i + 1] == 1)
            {
                int *aux = new int[2];
                aux[0] = pos;
                pos += scenario[level][i];
                aux[1] = pos;
                limRedFlat[level].push_back(aux);
            }
            else
            {
                int *aux = new int[2];
                aux[0] = pos;
                pos += scenario[level][i];
                aux[1] = pos;
                limBlackFlat[level].push_back(aux);
            }
        }
    }
}

void GameLogic::_moveReds(vector<int> &scenario, int *speed)
{
    if ((*speed) != 0)
    {
        for (std::size_t i = 0; i < scenario.size(); i += 2)
        {
            if (scenario[i + 1] == 1)
            {
                if ((*speed) > 0)
                {
                    if (scenario[i + 2] >= (*speed))
                    {
                        scenario[i + 2] -= (*speed);
                        scenario[i - 2] += (*speed);
                    }
                    else
                    {
                        (*speed) *= -1;
                    }
                }
                else
                {
                    if (scenario[i - 2] >= -1 * (*speed))
                    {
                        scenario[i - 2] += (*speed);
                        scenario[i + 2] -= (*speed);
                    }
                    else
                    {
                        (*speed) *= -1;
                    }
                }
            }
        }
        _vectorRestructuring();
    }
}

void GameLogic::scenarioDesign()
{
    for (int indice = 0; indice < level + 1; indice++)
    {
        _moveReds(scenario[indice], &(redSpeed[indice]));
        drawingLevel(radiusFromVectors[indice], DISTANCE_INTERPLATFORM * indice, (DISTANCE_INTERPLATFORM * indice) + 10, scenario[indice]);
    }
    for (int indice = level + 1; indice < NBR_LEVEL; indice++)
    {
        if (radiusFromVectors[indice])
            radiusFromVectors[indice] -= 0.5;
        drawingLevel(radiusFromVectors[indice], DISTANCE_INTERPLATFORM * (level + 1), (DISTANCE_INTERPLATFORM * (level + 1)) + 10, destroys);
    }
}

void GameLogic::_fillRadiusVector() {
    srand((unsigned)time(NULL));

    for (int i = 0; i < NBR_LEVEL; i++)
    {
        radiusFromVectors.push_back(50);
    }
}

void GameLogic::createScenarii()
{
    _fillRadiusVector();
    for (int indice = 0; indice < NBR_LEVEL; indice++)
    {
        int random = rand() % platformPatterns;
        if (random >= 8)
            redSpeed[indice] = (rand() % 2 == 0 ? -1 : 1) * (rand() % 4 + 1);
        else
            redSpeed[indice] = 0;
        int randomRotation = rand() % 30 + 20;

        patterns[random][0] = randomRotation;
        patterns[random][1] = rand() % 2 == 1 ? 0 : 2;
        scenario.push_back(patterns[random]);

        int pos = 0;
        for (std::size_t i = 0; i < patterns[random].size(); i += 2)
        {
            if (patterns[random][i + 1] == 0)
            {
                pos += patterns[random][i];
            }
            else
            {
                if (patterns[random][i + 1] == 1)
                {
                    int *aux = new int[2];
                    aux[0] = pos;
                    pos += patterns[random][i];
                    aux[1] = pos;
                    limRedFlat[indice].push_back(aux);
                }
                else
                {
                    int *aux = new int[2];
                    aux[0] = pos;
                    pos += patterns[random][i];
                    aux[1] = pos;
                    limBlackFlat[indice].push_back(aux);
                }
            }
        }
    }
}

void GameLogic::restartGame()
{
    for (int indice = 0; indice < NBR_LEVEL; indice++)
    {
        radiusFromVectors[indice] = 50;
    }
    utils::moveScreenX = 0;

    utils::translateSphere = INITIAL_POINT;
    level = NBR_LEVEL - 1;
    transposition = level * DISTANCE_INTERPLATFORM;
    utils::descent = level * DISTANCE_INTERPLATFORM;
    utils::pause = false;
}

namespace currentInstance {
    std::unique_ptr<GameLogic> gameLogic = std::make_unique<GameLogic>();
}
