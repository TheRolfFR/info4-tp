#ifndef BOUNDARIESMATERIAL_H
#define BOUNDARIESMATERIAL_H

#include "Material/material.h"

class BoundariesMaterial: public Material {
public:
    BoundariesMaterial(): Material("BoundariesMaterial") {
        setColor("diffuse", Color{255.0f, 255.0f, 255.0f, 0.5f});
        setDisplayMode(GL_LINE);
    }
    virtual ~BoundariesMaterial() {}
};

#endif // BOUNDARIESMATERIAL_H
