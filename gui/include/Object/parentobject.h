#pragma once

#include <string>
#include <vector>

#include <Object/object.h>

class View;

class ParentObject: public Object {
protected:
    std::vector<Object*> m_childs;
    std::shared_ptr<Shader> m_shader;

public:
    ParentObject(View* view, std::string &n);
    ParentObject(View* view, const char* n);
    virtual ~ParentObject();
    
    virtual void update(QMatrix4x4 &model, double t);

    void addChild(Object* obj) { m_childs.push_back(obj); };
    void removeChild(Object* obj);
    void clearChilds() { m_childs.clear(); };

    std::shared_ptr<Shader> getShader() { return m_shader; };
    void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; };
};
