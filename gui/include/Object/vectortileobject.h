#pragma once

#include <Object/tileobject.h>
#include <Common/color.h>

#include <ogr_geometry.h>
#include <ogr_spatialref.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>

#include <Data/vectortiledata.h>

class VectorTileObject : public TileObject {
public:
    VectorTileObject(View* view, int x, int y, int zoom);
    ~VectorTileObject();
};
