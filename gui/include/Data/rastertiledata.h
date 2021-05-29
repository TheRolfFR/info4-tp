#pragma once

#include <Data/uniquedata.h>
#include <Common/color.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>


class RasterTileData : public UniqueData {
public:
    RasterTileData(int x, int y, int zoom);
    ~RasterTileData();
};
