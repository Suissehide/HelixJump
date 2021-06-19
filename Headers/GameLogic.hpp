#if !defined(GameLogic_hpp)
#define GameLogic_hpp

#include <vector>

#include "GlutInit.hpp"

typedef struct vertices // Structure for storing vertices
{
    double x, y, z;
} vertice_t;

class GameLogic
{
private:
    std::vector<std::vector<int>> scenario;
    std::vector<int> radiusFromVectors;
    int level = NBR_LEVEL - 1;
    std::vector<std::vector<int *>> limBlackFlat = std::vector<std::vector<int *>>(NBR_LEVEL);
    std::vector<std::vector<int *>> limRedFlat = std::vector<std::vector<int *>>(NBR_LEVEL);


    void _fillRadiusVector();
    void _moveReds(std::vector<int> &scenario, int *speed);
    void _vectorRestructuring();
    float _freefall(float x);
    bool _touchedPlaneUpOnSameLevel(float positionBallX, float positionBallY, std::vector<int *> &limBlackFlat);
    bool _planeUnderBallSameLevel(std::vector<int *> &xPlan);
    void drawingCap(float ray, float height, bool Cover, std::vector<int> &vetor);
    void drawLateral(float ray, float start, float height, std::vector<int> &vetor);
    void drawMiddleSide(float start, float height, float g, bool frente, float ray);
    vertice_t *CalculatesNormal(float x1, float y1, float z1, float x2, float y2, float z2);
public:
    GameLogic()=default;
    ~GameLogic()=default;

    void lostGame();
    void drawingLevel(float ray, float start, float height, std::vector<int> &vetor);
    void createScenarii();
    void restartGame();
    void scenarioDesign();
    void drawsGame();
};

extern GameLogic gameLogicInstance;

#endif // GameLogic_hpp
