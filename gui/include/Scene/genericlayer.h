#pragma once

#include <string>
#include <vector>

#include <Material/material.h>
#include <Data/data.h>

#include <Scene/layer.h>

class GenericLayer: public Layer {
private:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Data> m_data;

public:
    GenericLayer(std::string &n, std::shared_ptr<Material> material, std::shared_ptr<Data> data);
    GenericLayer(const char* n, std::shared_ptr<Material> material, std::shared_ptr<Data> data);
    virtual ~GenericLayer();
    
    virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view);

    void setMaterial(std::shared_ptr<Material> material) { m_material = material; };
    void setData(std::shared_ptr<Data> data) { m_data = data; };
};
