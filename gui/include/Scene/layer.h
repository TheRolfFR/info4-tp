#pragma once

#include <string>
#include <vector>

#include <OpenGL/shader.h>
#include <Material/material.h>
#include <Data/data.h>

class ChildObject;

class Layer {
protected:
    std::vector<ChildObject*> m_childs;
    std::shared_ptr<Shader> m_shader;
    std::string m_name;

    bool m_hidden;

public:
    Layer(std::string &n);
    Layer(const char* n);
    virtual ~Layer();
    
    virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view) = 0;

    virtual void drawCheckbox(QWidget* tab, QLayout* layout);

    void addChild(ChildObject* obj) { m_childs.push_back(obj); };
    void removeChild(ChildObject* obj);

    std::shared_ptr<Shader> getShader() { return m_shader; };
    void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; };
    
    virtual void setHidden(bool h) { m_hidden = h; };
    virtual void setHidden() { m_hidden = true; };
    virtual void setVisible() { m_hidden = false; };
    virtual void toggleVisibility() { m_hidden = !m_hidden; };
};
