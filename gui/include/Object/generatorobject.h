/**
 * \file	generatorobject.h
 */
#pragma once

#include <Object/parentobject.h>

class Framebuffer;

class GeneratorObject : public ParentObject{
private:
    View* m_view;
    double m_last_t;

public:
    //*/ -------------------------------------------------
    GeneratorObject(View* view, std::string name);
    virtual ~GeneratorObject();

    void update(QMatrix4x4& model, double t);

    View* getView() { return m_view; };
    double getLastTime() { return m_last_t; };
};
