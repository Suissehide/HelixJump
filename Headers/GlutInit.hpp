#if !defined(GlutInit_hpp)
#define GlutInit_hpp

#define NBR_LEVEL 40
#define platformPatterns 10
#define PI 3.1415927
#define INITIAL_POINT 10 - sqrt(45 / 2)
#define DISTANCE_INTERPLATFORM 60

namespace utils
{
    extern float angle;
    extern float moveScreenX;
    extern bool Falling;
    extern bool pause;
    extern float descent;
    extern float translateSphere;
    extern float moveScreenX;
}

void idle();
void display();
void mouse(int button, int state, int x, int y);
void motion(int x, int);
void keyboard(unsigned char key, int, int);
void reshape(int w, int h);

#endif // GlutInit_hpp
