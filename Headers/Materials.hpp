#if !defined(Materials_hpp)
#define Materials_hpp

#include <GL/glut.h>

class Materials
{
private:
    // red material
    static void setMaterial1(void)
    {

        GLfloat object_environment[] = {.17, .01, .01, 0.55};
        GLfloat diffuse_object[] = {.61, .04, .04, 0.55};
        GLfloat specular_object[] = {.73, .63, .63, 0.55};
        GLfloat object_glitter[] = {77.0f};

        // Set the parameters of the surface to be illuminated
        glMaterialfv(GL_FRONT, GL_AMBIENT, object_environment);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_object);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_object);
        glMaterialfv(GL_FRONT, GL_SHININESS, object_glitter);
    }

    //black material
    static void setMaterial2(void)
    {

        GLfloat object_environment[] = {0, 0, 0, 1};
        GLfloat diffuse_object[] = {.01, .01, .01, 1.0};
        GLfloat specular_object[] = {.5, .5, .5, 1.0};
        GLfloat object_glitter[] = {32.0f};

        // Set the parameters of the surface to be illuminated
        glMaterialfv(GL_FRONT, GL_AMBIENT, object_environment);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_object);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_object);
        glMaterialfv(GL_FRONT, GL_SHININESS, object_glitter);
    }

    static void setMaterial3(void)
    {

        GLfloat object_environment[] = {.11, .06, .11, 1.0};
        GLfloat diffuse_object[] = {.43, .47, .54, 1.0};
        GLfloat specular_object[] = {.33, .33, .52, 1.0};
        GLfloat object_glitter[] = {10.0f};

        // Set the parameters of the surface to be illuminated
        glMaterialfv(GL_FRONT, GL_AMBIENT, object_environment);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_object);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_object);
        glMaterialfv(GL_FRONT, GL_SHININESS, object_glitter);
    }

    //grey material
    static void setMaterial4(void)
    {

        GLfloat object_environment[] = {.25, .25, .25, 1}; //.55
        GLfloat diffuse_object[] = {.40, .40, .40, 1};
        GLfloat specular_object[] = {.77, .77, .77, 1};
        GLfloat object_glitter[] = {77.0f};

        // Set the parameters of the surface to be illuminated
        glMaterialfv(GL_FRONT, GL_AMBIENT, object_environment);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_object);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_object);
        glMaterialfv(GL_FRONT, GL_SHININESS, object_glitter);
    }

    static void setMaterial5(void)
    {

        GLfloat object_environment[] = {.25, .21, .21, .92};
        GLfloat diffuse_object[] = {1, .83, .83, .92};
        GLfloat specular_object[] = {.3, .30, .30, .92};
        GLfloat object_glitter[] = {11.0f};

        // Set the parameters of the surface to be illuminated
        glMaterialfv(GL_FRONT, GL_AMBIENT, object_environment);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_object);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_object);
        glMaterialfv(GL_FRONT, GL_SHININESS, object_glitter);
    }

    //yellow material
    static void setMaterial6(void)
    {

        GLfloat object_environment[] = {.33, .22, .03, 1.0};
        GLfloat diffuse_object[] = {.78, .57, .11, 1.0};
        GLfloat specular_object[] = {.99, .94, .81, 1.0};
        GLfloat object_glitter[] = {28.0f};

        // Set the parameters of the surface to be illuminated
        glMaterialfv(GL_FRONT, GL_AMBIENT, object_environment);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_object);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_object);
        glMaterialfv(GL_FRONT, GL_SHININESS, object_glitter);
    }
public:
    Materials() = delete;
    ~Materials() = delete;

    static void setMaterial(int tipo)
    {
        switch (tipo)
        {
        case 1:
            setMaterial1();
            break;
        case 2:
            setMaterial2();
            break;
        case 3:
            setMaterial3();
            break;
        case 4:
            setMaterial4();
            break;
        case 7:
            setMaterial6();
            break;

        default:
            break;
        }
    }
};

#endif // Materials_hpp
