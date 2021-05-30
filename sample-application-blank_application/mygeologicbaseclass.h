#ifndef MYGEOLOGICBASECLASS_H
#define MYGEOLOGICBASECLASS_H

#include <OpenGL/scenemanager.h>

class MyGeologicBaseClass : public SceneManager
{
public:
    MyGeologicBaseClass();

    void init();
    void draw();
    double update() {}
    void realUpdate(double t) {}
    void resize(QVector2D& size) {}
};

#endif // MYGEOLOGICBASECLASS_H
