#ifndef OGR_POINT_MATERIAL_H
#define OGR_POINT_MATERIAL_H

#include <Material/material.h>

class ogr_point_material : public Material {
public:
    ogr_point_material(float r, float g, float b, float a, float pt_size);
    virtual ~ogr_point_material() {}
};

#endif // OGR_POINT_MATERIAL_H
