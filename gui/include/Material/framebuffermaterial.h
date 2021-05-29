#pragma once

#include <Material/material.h>

class FramebufferMaterial: public Material {
public:
    FramebufferMaterial(std::shared_ptr<Shader> shader);
    virtual ~FramebufferMaterial();
};
