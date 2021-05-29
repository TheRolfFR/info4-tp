#pragma once

#include <string>
#include <vector>
#include <memory>

#include <Object/object.h>

#include <OpenGL/shader.h>
#include <Material/material.h>
#include <Data/data.h>

#include <Scene/view.h>

class Layer;

class ChildObject: public Object {
protected:
    std::shared_ptr<Data> m_data;
    std::shared_ptr<Material> m_material;
    Layer* m_render_layer;

    void setData(std::shared_ptr<Data> d) { m_data = move(d); };
    void setMaterial(std::shared_ptr<Material> m) { m_material = move(m); };

public:
    ChildObject(std::string &n);
    ChildObject(const char* n);
    virtual ~ChildObject();
    
    virtual void draw(Shader* shader);

    std::shared_ptr<Data>& getData() { return m_data; };
    std::shared_ptr<Material>& getMaterial() { return m_material; };
};
