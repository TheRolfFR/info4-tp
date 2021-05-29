#ifndef QUADDISPLAYER_H
#define QUADDISPLAYER_H

#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <OpenGL/texture.h>
#include <Common/color.h>
#include <string>
#include <Common/color.h>

class QuadDisplayer {
public:
    QuadDisplayer();
    static void draw(OGRPoint corners[4], const std::string &texture_file, OGRSpatialReference *to);
    static void drawQuad(OGRPoint* corners[4]);
    static void drawQuad(OGRPoint* corners[4], Color color);
};

#endif // QUADDISPLAYER_H
