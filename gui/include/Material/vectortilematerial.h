#pragma once

#include <Material/material.h>

class VectorTileMaterial: public Material {
private:
    std::shared_ptr<Texture> m_tileTexture;

public:
    VectorTileMaterial();
    virtual ~VectorTileMaterial();
};
