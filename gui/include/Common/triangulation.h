#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <iostream>
#include <vector>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <memory>

class Triangulation {
public:
    static std::vector<float> triangulate_ear(OGRMultiPolygon *polygons);
};

#endif // TRIANGULATION_H
