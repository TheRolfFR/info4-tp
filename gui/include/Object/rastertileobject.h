#pragma once

#include <Object/tileobject.h>
#include <Common/color.h>

#include <ogr_geometry.h>
#include <ogr_spatialref.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>

class RasterTileObject : public TileObject {
    public:
        RasterTileObject(View* view, int x, int y, int zoom);
        ~RasterTileObject();
};
