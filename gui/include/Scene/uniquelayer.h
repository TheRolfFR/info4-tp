#pragma once

#include <string>
#include <vector>

#include <Material/material.h>
#include <Data/data.h>

#include <Scene/layer.h>

class UniqueLayer: public Layer {
public:
    UniqueLayer(std::string &n);
    UniqueLayer(const char* n);
    virtual ~UniqueLayer();
    
    virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view);
};
