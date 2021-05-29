#pragma once

#include <Material/material.h>

class RasterTileMaterial: public Material {
public:
    RasterTileMaterial(int x, int y, int z);
    virtual ~RasterTileMaterial();
};
