#pragma once

#include <Object/childobject.h>

#include <iostream>
#include <OpenGL/shader.h>

class BackgroundObject : public ChildObject {
protected:
    std::shared_ptr<Shader> m_shader;

public:
    BackgroundObject(double r, double g, double b, double a);
    ~BackgroundObject();

    void draw();
};
